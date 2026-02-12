#pragma once

#include "TimeStep.h"

#include "Cobweb/Events/Events.h"

#include <string>

namespace Cobweb
{
	class Layer
	{
	public:
		Layer(const std::string &name = "Layer")
			: m_Name(name)
		{
		}

		virtual ~Layer() = default;

		virtual inline void OnAttach() {}
		virtual inline void OnDetach() {}
		virtual inline void OnUpdate(TimeStep ts) {}
		virtual inline void OnImGuiDraw() {}
		virtual inline void OnEvent(Event &e) {}

		inline const std::string &GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
}
