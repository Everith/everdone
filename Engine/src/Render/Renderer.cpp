#include "Renderer.h"
#include "GL/render_GL.h"
#include "GL/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <conio.h>

#include "../Input/Input.h"

Renderer::Renderer(/*GLFWwindow* m_WindowID*/)
{
	l.Report("Renderer CLASS");
	//GL Window tulajdonságai
	const char* window_name = "OpenGL Window";
	int width = 1920;
	int height = 1080;

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	m_WindowID = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
	//m_WindowID = &w;
	if (!m_WindowID) { glfwTerminate(); }
	glfwSetWindowPos(m_WindowID, 870, 250);
	glfwMakeContextCurrent(m_WindowID);
	if (glewInit()) {
		l.Error("GLEW inditási hiba!");
		std::cout << glewInit() << std::endl;
	}
	// limitálfa a FPS-t
	glfwSwapInterval(1);
	//A video kártya tipusa kiírása :
	std::cout << "A grafikus szoftver verzioszáma: " << glGetString(GL_VERSION) << std::endl;
}

Renderer::~Renderer()
{
	glfwDestroyWindow(m_WindowID);
	glfwTerminate();
}

void Renderer::DrawImage(const std::string& path, int x, int y) const
{
	GL oGL;
	double arany = 1920.0f / 1080.0f;
	double imArany = (double)x / (double)y;

	int a = x / 2;
	int b = y / 2;
	int a1 = x / 3;
	int b1 = y / 3;

	if (imArany <= arany + 0.1f && imArany >= arany - 0.1f)
	{//desktop
		glfwSetWindowPos(m_WindowID, 900, 250);
		glfwSetWindowSize(m_WindowID, 960, 540);
	}
	else
	{//mobile
		glfwSetWindowPos(m_WindowID, 1500, 250);
		glfwSetWindowSize(m_WindowID, 370, 580);
	}
	oGL.Image(path, x, y);

	glfwSwapBuffers(m_WindowID);
	glfwPollEvents();
}

void Renderer::DrawImage1(const std::string& path, int x, int y) const
{
	GL oGL;
	double b = 0.0f;
	double a = 0.0f;
	double Ax = ((double)x / 1920.0f) * 1.2;
	double Ay = ((double)y / 1080.0f) * 1.2;

	if (Ax > Ay)
	{
		if (Ax < 1)
		{
			b = y;
			a = x;
		}
		else {
			b = y / Ax;
			a = x / Ax;
		}
	}
	else
	{
		if (Ay < 1)
		{
			b = y;
			a = x;
		}
		else {
			b = y / Ay;
			a = x / Ay;
		}
	}

	glfwSetWindowPos(m_WindowID, 1900 - a, 980 - b);
	glfwSetWindowSize(m_WindowID, a, b);

	oGL.Image1(path, a, b);
	glfwSwapBuffers(m_WindowID);
	glfwPollEvents();
}

void Renderer::Teszt()
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
	//Blending Engedélyezése
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Vertex Buffer :
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexArray va;
	VertexBuffer vb(pozicio, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.addBuffer(vb, layout);

	// Index buffer:
	IndexBuffer ib(indecis, 6);

	// Shader:
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	//A shader helyének megadása inicializálásnál
	Shader shader("SRC\\source\\Render\\shader\\Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);
	shader.SetUniformMat4f("u_MVP", proj);

	Texture texture(L"Data\\Profile_Image.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	GL render;
	Everith::Log l;
	// Main loop:
	while (!glfwWindowShouldClose(m_WindowID)) {
		render.Clear();
		render.Draw(va, ib, shader);
		glfwSwapBuffers(m_WindowID);
		glfwPollEvents();

		//Inputs
		Input i;
		int key;
		key = i.get_KeyCallback();

		//glfwSetKeyCallback (m_WindowID, Input::key_callback);
		if (glfwGetKey(m_WindowID, GLFW_KEY_E)) { l.Pass("E is pressed"); }
	}
}