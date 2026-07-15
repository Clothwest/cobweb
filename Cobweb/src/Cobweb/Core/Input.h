#pragma once

#include "KeyCodes.h"

#include <utility>

namespace Cobweb
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePos();

		static bool IsMouseButtonPressed(MouseButton button);
	};
}
