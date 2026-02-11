#pragma once

#include "Cobweb/Renderer/VertexArray.h"

namespace Cobweb
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer> &vbo) override;
		void SetIndexBuffer(const Ref<IndexBuffer> &ibo) override;

		inline const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override { return m_VertexBuffers; }
		inline const Ref<IndexBuffer> &GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		uint32_t m_AttribLocation = 0;
		uint32_t m_BindingIndex = 0;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
