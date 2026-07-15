#pragma once

#include "Cobweb/Core/Base.h"

#include <utility>
#include <string>

namespace Cobweb
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetID() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual std::pair<int, int> GetSize() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	protected:
		Texture() = default;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(int width, int height);
		static Ref<Texture2D> Create(const std::string &filePath);

	public:
		virtual ~Texture2D() = default;

		virtual void SetData(const void *data, uint32_t size) const = 0;

	protected:
		Texture2D() = default;
	};
}
