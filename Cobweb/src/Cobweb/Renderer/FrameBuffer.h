#pragma once

#include "Cobweb/Core/Base.h"

namespace Cobweb
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
	};

	class FrameBuffer
	{
	public:
		static Ref<FrameBuffer> Create(const FrameBufferSpecification &spec);

	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const FrameBufferSpecification &GetSpecification() const = 0;
		virtual uint32_t GetTextureID() const = 0;
	};
}
