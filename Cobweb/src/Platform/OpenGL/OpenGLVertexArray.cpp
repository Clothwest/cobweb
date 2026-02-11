#include "cwpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Cobweb
{
	GLenum s_ShaderDataTypeToOpenGLType(ShaderDataType type);

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vbo)
	{
		CW_CORE_ASSERT(vbo->GetLayout().GetCount() > 0, "VertexBuffer has no layout!");

		glVertexArrayVertexBuffer(m_RendererID, m_BindingIndex, vbo->GetID(), 0, vbo->GetLayout().GetStride());

		for (const BufferElement &element : vbo->GetLayout())
		{
			glEnableVertexArrayAttrib(m_RendererID, m_AttribLocation);
			glVertexArrayAttribFormat(m_RendererID, m_AttribLocation, element.Count, s_ShaderDataTypeToOpenGLType(element.Type), element.Normalized, element.Offset);
			glVertexArrayAttribBinding(m_RendererID, m_AttribLocation, m_BindingIndex);
			m_AttribLocation++;
		}

		m_VertexBuffers.push_back(vbo);
		m_BindingIndex++;
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &ibo)
	{
		glVertexArrayElementBuffer(m_RendererID, ibo->GetID());
		m_IndexBuffer = ibo;
	}

	GLenum s_ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return GL_FLOAT;
			case ShaderDataType::Float2:  return GL_FLOAT;
			case ShaderDataType::Float3:  return GL_FLOAT;
			case ShaderDataType::Float4:  return GL_FLOAT;
			case ShaderDataType::Int:     return GL_INT;
			case ShaderDataType::Int2:    return GL_INT;
			case ShaderDataType::Int3:    return GL_INT;
			case ShaderDataType::Int4:    return GL_INT;
			case ShaderDataType::Mat3:    return GL_FLOAT;
			case ShaderDataType::Mat4:    return GL_FLOAT;
			case ShaderDataType::Bool:    return GL_BOOL;
		}

		CW_CORE_ASSERT(false, "Unkown ShaderDataType");
		return GL_NONE;
	}
}
