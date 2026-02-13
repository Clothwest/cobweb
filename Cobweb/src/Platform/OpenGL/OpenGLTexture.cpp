#include "cwpch.h"
#include "OpenGLTexture.h"

#include <stb_image/stb_image.h>

#include <glad/glad.h>

namespace Cobweb
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string &filePath)
	{
		stbi_set_flip_vertically_on_load(1);

		int channels;
		stbi_uc *data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &channels, 0);
		CW_CORE_ASSERT(data, "Unable to load file!");

		GLenum internalFormat = GL_NONE, dataFormat = GL_NONE;
		switch (channels)
		{
			case 4:
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			case 3:
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			default:
				CW_CORE_ASSERT(false, "Unknown channels!");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
