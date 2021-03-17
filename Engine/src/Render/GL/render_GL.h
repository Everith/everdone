#pragma once
#include "..\..\Core.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <sstream>
#include <stdio.h>

#include "../../File/file.h"

#include "..\Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class GL {
private:
    GLFWwindow* m_Window;
public:
    void Draw (VertexArray& va, IndexBuffer& ib, Shader& shader) const;
    void Clear ()const;

    void Image (const std::wstring& path, int x, int y) const;
    void Image1 (const std::wstring& path, int x, int y) const;
};
