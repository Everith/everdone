#include "Texture.h"
#include <locale>
#include <codecvt>

#define glBindTextures

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

Texture::Texture (const std::wstring& path) :m_RenderID (0), m_Filepath (path), m_LocalBuffer (nullptr), m_Width (0), m_Height (0), m_BPP (0)
{
    stbi_set_flip_vertically_on_load (1);

	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string path_str = converter.to_bytes (path);
	
	m_LocalBuffer = stbi_load (path_str.c_str() , &m_Width, &m_Height, &m_BPP, 4);

    glGenTextures (1, &m_RenderID);
    glBindTextures (GL_TEXTURE_2D, m_RenderID);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTextures (GL_TEXTURE_2D, 0);

    if (m_LocalBuffer)
    {
        stbi_image_free (m_LocalBuffer);
    }
}

Texture::~Texture ()
{
    glDeleteTextures (1, &m_RenderID);
}

void Texture::Bind (unsigned int slot /*= 0*/)
{
    glActiveTexture (GL_TEXTURE0 + slot);
    glBindTextures (GL_TEXTURE_2D, m_RenderID);
}

void Texture::Unbind ()
{
    glBindTextures (GL_TEXTURE_2D, 0);
}