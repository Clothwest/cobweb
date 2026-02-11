#include "cwpch.h"
#include "VertexBuffer.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"

#include "Cobweb/Core/Log.h"

namespace Cobweb
{
	static uint32_t s_ShaderDataTypeCount(ShaderDataType type);
	static uint32_t s_ShaderDataTypeSize(ShaderDataType type);

	Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized)
		: Type(type), Name(name), Normalized(normalized), Count(s_ShaderDataTypeCount(type)), Size(s_ShaderDataTypeSize(type)), Offset(0)
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &list)
		: m_Elements(list)
	{
		CalculateOffsetAndStride();
		m_Count = (uint32_t)m_Elements.size();
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		for (BufferElement &element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
		}
		m_Stride = offset;
	}

	uint32_t s_ShaderDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;

			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;

			case ShaderDataType::Mat3:    return 4 * 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4 * 4;

			case ShaderDataType::Bool:    return 1;
		}
		
		CW_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	uint32_t s_ShaderDataTypeSize(ShaderDataType type)
	{
		uint32_t count = s_ShaderDataTypeCount(type);
		CW_CORE_ASSERT(count > 0, "Unknown ShaderDataType!");
		if (type == ShaderDataType::Bool)
			return 1;
		else
			return count * 4;
	}
}
