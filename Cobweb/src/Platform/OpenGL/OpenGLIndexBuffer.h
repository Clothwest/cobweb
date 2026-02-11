#pragma once

#include "Cobweb/Renderer/IndexBuffer.h"

namespace Cobweb
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
		~OpenGLIndexBuffer();

		inline uint32_t GetID() const override { return m_RendererID; }
		inline uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
