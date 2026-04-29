#pragma once

#include "Texture.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &coord, const glm::vec2 &size);

		inline const glm::vec2 *GetCoords() const { return m_Coords; }

		inline const Ref<Texture2D> &GetTexture() const { return m_Texture; }
		inline uint32_t GetID() const { return m_Texture->GetID(); }

	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_Coords[4];
	};
}
