#include "render_GL.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void GL::Draw (VertexArray& va, IndexBuffer& ib, Shader& shader) const
{
    shader.Bind ();
    va.Bind ();
    ib.Bind ();
    glDrawElements (GL_TRIANGLES, ib.GetCount (), GL_UNSIGNED_INT, nullptr);
}

void GL::Clear ()const
{
    glClear (GL_COLOR_BUFFER_BIT);
}

void GL::Image (const std::wstring& path, int x, int y) const
{
    // Vertex pozicío
    float pozicio[]{
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    // Vertex beolvasási utasítás:
    unsigned int indecis[] = {
        0, 1, 2,
        2, 3, 0
    };

    //##############################################################################################################
    //##############################################################################################################
    //##############################################################################################################
    //##############################################################################################################
    //Blending Engedélyezése
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_BLEND);

    // Vertex Buffer :
    unsigned int vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    VertexArray va;
    VertexBuffer vb (pozicio, 4 * 4 * sizeof (float));

    VertexBufferLayout layout;
    layout.Push<float> (2);
    layout.Push<float> (2);
    va.addBuffer (vb, layout);

    // Index buffer:
    IndexBuffer ib (indecis, 6);

    // Shader:
    double Desktop = 1920.0 / 1080.0;
    double Moblie = 1080.0 / 1920.0;

    double arany = (double)x / (double)y;
    glm::mat4 proj = glm::ortho (-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    if (arany <= Desktop + 0.1 && arany >= Desktop - 0.1)
    {//Desktop
        proj = glm::ortho (-1.0f, 1.0f, -1.0f, 1.22f, -1.0f, 1.0f);
    }
    else if (arany <= Moblie + 0.1 && arany >= Moblie - 0.1)
    {//Mobile
        proj = glm::ortho (-1.0f, 4.42f, -1.0f, 1.07f, -1.0f, 1.0f);
    }

    //A shader helyének megadása inicializálásnál
    Shader shader ("SRC\\source\\Render\\shader\\Basic.shader");
    shader.Bind ();
    shader.SetUniform4f ("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);
    shader.SetUniformMat4f ("u_MVP", proj);

    Texture texture (path);
    texture.Bind ();
    shader.SetUniform1i ("u_Texture", 0);

    Clear ();
    Draw (va, ib, shader);

    //ezeket nem értem itt lehetnek ha kellenek a késöbbiekben
    //va.Unbind ();
    //vb.Unbind ();
    //ib.Unbind ();
    //shader.Unbind ();
}
void GL::Image1 (const std::wstring& path, int x, int y) const
{
    //double xx = (double)y / (double)x;
    //double yy = (double)x / (double)y;
    //double atlagArany = 1080.0f / (((double)x + (double)y) / 2);
    double ax = (1920.0f / (double)x);
    double ay = (1080.0f / (double)y);

    glm::mat4 proj = glm::ortho (-1.0f, (float)ax, -1.0f, (float)ay * 0.97f, -1.0f, 1.0f);

    // Vertex pozicío
    float pozicio[]{
        // xxxx   yyyy  zzzz  cccc
          -1.0f,               -1.0f,                0.0f, 0.0f,
           1.0f / (float)ax ,   -1.0f,                1.0f, 0.0f,
           1.0f / (float)ax ,    1.0f / (float)ay ,    1.0f, 1.0f,
          -1.0f,                1.0f / (float)ay ,    0.0f, 1.0f,
    };

    // Vertex beolvasási utasítás:
    unsigned int indecis[] = {
        0, 1, 2,
        2, 3, 0
    };

    //##############################################################################################################
    //##############################################################################################################
    //##############################################################################################################
    //##############################################################################################################
    //Blending Engedélyezése
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_BLEND);

    // Vertex Buffer :
    unsigned int vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    VertexArray va;
    VertexBuffer vb (pozicio, 4 * 4 * sizeof (float));

    VertexBufferLayout layout;
    layout.Push<float> (2);
    layout.Push<float> (2);
    va.addBuffer (vb, layout);

    // Index buffer:
    IndexBuffer ib (indecis, 6);

    // Shader:

    //if (arany <= Desktop + 0.1 && arany >= Desktop - 0.1)
    //{//Desktop
    //    proj = glm::ortho (-1.0f, 1.0f, -1.0f, 1.22f, -1.0f, 1.0f);
    //}
    //else if (arany <= Moblie + 0.1 && arany >= Moblie - 0.1)
    //{//Mobile
    //    proj = glm::ortho (-1.0f, 4.42f, -1.0f, 1.07f, -1.0f, 1.0f);
    //}

    //A shader helyének megadása inicializálásnál
    Shader shader ("Everith\\source\\Render\\shader\\Basic.shader");
    shader.Bind ();
    shader.SetUniform4f ("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);
    shader.SetUniformMat4f ("u_MVP", proj);

    Texture texture (path);
    texture.Bind ();
    shader.SetUniform1i ("u_Texture", 0);

    Clear ();
    Draw (va, ib, shader);

    //ezeket nem értem itt lehetnek ha kellenek a késöbbiekben
    //va.Unbind ();
    //vb.Unbind ();
    //ib.Unbind ();
    //shader.Unbind ();
}