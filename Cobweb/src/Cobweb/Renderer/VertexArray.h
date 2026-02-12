#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Cobweb/Core/Core.h"

#include <vector>

namespace Cobweb
{
	class VertexArray
	{
	public:
		static Ref<VertexArray> Create();

	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer> &vbo) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> &ibo) = 0;

		virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;

	protected:
		VertexArray() = default;
	};
}
