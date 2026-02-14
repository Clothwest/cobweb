#pragma once

#include "Cobweb/Renderer/Texture.h"

namespace Cobweb
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string &filePath);
		~OpenGLTexture2D();

		inline int GetWidth() const override { return m_Width; }
		inline int GetHeight() const override { return m_Height; }
		inline std::pair<int, int> GetSize() const override { return { m_Width, m_Height }; }

		void Bind(uint32_t slot = 10) const override;

	private:
		uint32_t m_RendererID;

		int m_Width, m_Height;
	};
}
