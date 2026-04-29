#include "cwpch.h"
#include "SubTexture.h"

namespace Cobweb
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D> &texture,const glm::vec2 &coord, const glm::vec2 &size)
		: m_Texture(texture)
	{
		m_Coords[0] = coord;
		m_Coords[1] = { coord.x + size.x, coord.y };
		m_Coords[2] = { coord.x + size.x, coord.y + size.y };
		m_Coords[3] = { coord.x, coord.y + size.y };

		auto &[width, height] = m_Texture->GetSize();
		for (int i = 0; i < 4; i++)
		{
			m_Coords[i].x /= width;
			m_Coords[i].y /= height;
		}
	}
}
