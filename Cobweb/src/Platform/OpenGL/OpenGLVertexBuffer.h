#pragma once

#include "Cobweb/Renderer/VertexBuffer.h"

namespace Cobweb
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float *vertices, uint32_t size);
		~OpenGLVertexBuffer();

		inline uint32_t GetID() const override { return m_RendererID; }

		inline void SetLayout(const BufferLayout &layout) override { m_Layout = layout; }
		inline const BufferLayout &GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}
