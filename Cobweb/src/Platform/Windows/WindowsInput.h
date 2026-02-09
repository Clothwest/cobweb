#pragma once

#include "Cobweb/Core/Input.h"

namespace Cobweb
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;
		~WindowsInput() = default;

	private:
		bool IsKeyPressedImpl(int keyCode) const override;

		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
		std::pair<float, float> GetMousePosImpl() const override;

		bool IsMouseButtonPressedImpl(int button) const override;
	};
}
