#pragma once

#include "GL\glew.h"
//#include "GLFW\glfw3.h"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    IndexBuffer (const unsigned int* data, unsigned int Count);
    ~IndexBuffer ();

    void Bind () const;
    void Unbind () const;

    //Getter
    inline unsigned int GetCount () const { return m_Count; }
protected:
};
