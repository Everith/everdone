#pragma once

#include <vector>
#include "GL\glew.h"
#include "..\Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int GetSizeOfType (unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 4;
        }
        // ha van assert error handeling
        //ASSERT (false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout () : m_Stride (0) {}

    template<typename T>
    void Push (unsigned int count)
    {
        static_assert(false);
    }

    template<>
    void Push<float> (unsigned int count)
    {
        //TODO Normalized valeu is hardcoded false at the moment
        m_Elements.push_back ({ GL_FLOAT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType (GL_FLOAT); // a haszn?lt adategys?g m?ret?vel n?velj?k
    }

    template<>
    void Push<unsigned int > (unsigned int count)
    {
        //TODO Normalized valeu is hardcoded false at the moment
        m_Elements.push_back ({ GL_UNSIGNED_INT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType (GL_UNSIGNED_INT); // a haszn?lt adategys?g m?ret?vel n?velj?k
    }

    template<>
    void Push<unsigned char > (unsigned int count)
    {
        //TODO Normalized valeu is hardcoded false at the moment
        m_Elements.push_back ({ GL_UNSIGNED_BYTE, count, true });
        m_Stride += count * VertexBufferElement::GetSizeOfType (GL_UNSIGNED_BYTE); // a haszn?lt adategys?g m?ret?vel n?velj?k
    }

    inline const std::vector<VertexBufferElement> GetElements () const { return m_Elements; }
    inline unsigned int GetStride () const { return m_Stride; }
};
