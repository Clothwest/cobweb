#pragma once

#include "Cobweb/Renderer/UniformBuffer.h"

namespace Cobweb
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t bindingIndex);
		~OpenGLUniformBuffer();

		void SetData(const void *data, uint32_t size, uint32_t offset = 0) const override;

	private:
		uint32_t m_RendererID;
	};
}
