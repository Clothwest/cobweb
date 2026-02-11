#pragma once

#include "Cobweb/Core/Core.h"

namespace Cobweb
{
	class IndexBuffer
	{
	public:
		static Ref<IndexBuffer> Create(uint32_t *indices, uint32_t count);

	public:
		virtual ~IndexBuffer() = default;

		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetCount() const = 0;

	protected:
		IndexBuffer() = default;
	};
}
