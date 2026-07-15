#pragma once

#include "Cobweb/Renderer/FrameBuffer.h"

namespace Cobweb
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification &spec);
		~OpenGLFrameBuffer();

		void Bind() const override;
		void UnBind() const override;

		void Resize(uint32_t width, uint32_t height) override;

		const FrameBufferSpecification &GetSpecification() const override;
		uint32_t GetTextureID() const override;

	private:
		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;

		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
	};
}
