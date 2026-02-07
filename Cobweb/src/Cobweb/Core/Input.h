#pragma once

#include <utility>

namespace Cobweb
{
	class Input
	{
	public:
		static inline bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		static inline float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		static inline std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

		static inline bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

	public:
		virtual ~Input() = default;

	protected:
		Input() = default;

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) const = 0;

		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
		virtual std::pair<float, float> GetMousePosImpl() const = 0;

		virtual bool IsMouseButtonPressedImpl(int button) const = 0;

	private:
		static Input *s_Instance;
	};
}
