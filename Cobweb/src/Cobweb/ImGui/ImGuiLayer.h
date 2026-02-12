#pragma once

#include "Cobweb/Core/Layer.h"

namespace Cobweb
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiDraw() override;
		void OnEvent(Event &e) override;

		void Begin();
		void End();
	};
}
