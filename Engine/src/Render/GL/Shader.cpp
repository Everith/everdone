#include "Shader.h"
#include "render_GL.h"
#include "../../Log/Log.h"

Shader::Shader (const std::string& filepath) : m_FilePath (filepath), m_RendererID (0)
{
    shaderSource sSource = GetShader (filepath);
    m_RendererID = CreateShader (sSource.shaderVertex, sSource.shaderFregment);
}

Shader::~Shader ()
{
    glDeleteProgram (m_RendererID);
}

void Shader::Bind () const
{
    glUseProgram (m_RendererID);
}

void Shader::Unbind () const
{
    glUseProgram (0);
}

void Shader::SetUniform1i (const std::string& name, int value)
{
    glUniform1i (GetUniformLocation (name), value);
}

void Shader::SetUniform1f (const std::string& name, float value)
{
    glUniform1f (GetUniformLocation (name), value);
}

// Uniform a shaderben a változo amit megkereshetunk a glUnitLocation functionnal
void Shader::SetUniform4f (const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f (GetUniformLocation (name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f (const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv (GetUniformLocation (name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation (const std::string& name)
{
    //Uniform Location Cache
    if (m_UniformLocationCache.find (name) != m_UniformLocationCache.end ())
    {
        return m_UniformLocationCache[name];
    }
    int location = glGetUniformLocation (m_RendererID, name.c_str ());
    if (location == -1)
    {
        //EVERITH::LogError ("Warnig: Missing uniform: ", name.c_str ());
    }
    m_UniformLocationCache[name] = location;
    return location;
}

// Extract shader code from file and split it to vertex and fragment shader
shaderSource Shader::GetShader (const std::string path) {
    std::ifstream stream (path);
    enum class shaderType {
        NONE = -1, VERTEX = 0, FREGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    while (getline (stream, line)) {
        if (line.find ("#shader") != std::string::npos) {
            if (line.find ("vertex") != std::string::npos) {
                type = shaderType::VERTEX;
            }
            else if (line.find ("fragment") != std::string::npos) {
                type = shaderType::FREGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str (), ss[1].str () };
}

// Compile shader
unsigned int Shader::CompileShader (unsigned int type, const std::string shaderSource) {
    unsigned int id = glCreateShader (type);
    const char *scr = shaderSource.c_str ();
    glShaderSource (id, 1, &scr, nullptr);
    glCompileShader (id);

    int result;
    glGetShaderiv (id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char*)alloca (length * sizeof (char));
        glGetShaderInfoLog (id, length, &length, message);
        //Error ("Failed to compile");
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader (id);
        return 0;
    }
    return id;
}

// Attach shader to program
unsigned int Shader::CreateShader (const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram ();
    unsigned int vShader = CompileShader (GL_VERTEX_SHADER, vertexShader);
    unsigned int fShader = CompileShader (GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader (program, vShader);
    glAttachShader (program, fShader);
    glLinkProgram (program);
    glValidateProgram (program);

    glDeleteShader (vShader);
    glDeleteShader (fShader);

    return program;
}