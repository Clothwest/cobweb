#pragma once

#include "Cobweb/Core/Core.h"

namespace Cobweb
{
	class UniformBuffer
	{
	public:
		static Ref<UniformBuffer> Create(uint32_t size, uint32_t bindingIndex);

	public:
		virtual ~UniformBuffer() = default;

		virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) const = 0;

	protected:
		UniformBuffer() = default;
	};
}
