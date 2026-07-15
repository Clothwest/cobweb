#pragma once

#include "Cobweb/Core/Base.h"

#include <string>
#include <vector>
#include <initializer_list>

namespace Cobweb
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		bool Normalized;

		uint32_t Count;
		uint32_t Size;
		uint32_t Offset;

		BufferElement(ShaderDataType type, const std::string &name, bool normalized = false);
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement> &list);
		~BufferLayout() = default;

		inline const std::vector<BufferElement> &GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }
		inline uint32_t GetCount() const { return m_Count; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
		uint32_t m_Count = 0;
	};

	class VertexBuffer
	{
	public:
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float *vertices, uint32_t size);

	public:
		virtual ~VertexBuffer() = default;

		virtual uint32_t GetID() const = 0;

		virtual void SetData(void *data, uint32_t size) const = 0;

		virtual void SetLayout(const BufferLayout &layout) = 0;
		virtual const BufferLayout &GetLayout() const = 0;

	protected:
		VertexBuffer() = default;
	};
}
