#pragma once

#include <string>
#include "GL/glew.h"

class Texture
{
private:
    unsigned int m_RenderID;
    std::wstring m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture (const std::wstring& path);
    ~Texture ();

    void Bind (unsigned int slot = 0);
    void Unbind ();

    inline int GetWidth () const { return m_Width; }
    inline int GetHeight () const { return m_Height; }
};
