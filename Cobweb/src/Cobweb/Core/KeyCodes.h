#pragma once

#include <ostream>

namespace Cobweb
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h

		/* Printable keys */
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		BackSlash = 92, /* \ */
		RightBracket = 93, /* ] */
		GraveAccent = 96, /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* KeyPad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348,

		Last = Menu
	} Key;

	typedef enum class MouseButton : uint16_t
	{
		// From glfw3.h

		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

		Last = Button8,
		Left = Button1,
		Right = Button2,
		Middle = Button3
	} Button;

	inline std::ostream &operator<<(std::ostream &os, KeyCode key)
	{
		return os << static_cast<uint32_t>(key);
	}

	inline std::ostream &operator<<(std::ostream &os, MouseButton button)
	{
		return os << static_cast<uint32_t>(button);
	}
}

// From glfw3.h

/* Printable keys */
#define CW_KEY_SPACE              ::Cobweb::Key::Space
#define CW_KEY_APOSTROPHE         ::Cobweb::Key::Apostrophe  /* ' */
#define CW_KEY_COMMA              ::Cobweb::Key::Comma  /* , */
#define CW_KEY_MINUS              ::Cobweb::Key::Minus  /* - */
#define CW_KEY_PERIOD             ::Cobweb::Key::Period  /* . */
#define CW_KEY_SLASH              ::Cobweb::Key::Slash  /* / */
#define CW_KEY_0                  ::Cobweb::Key::D0
#define CW_KEY_1                  ::Cobweb::Key::D1
#define CW_KEY_2                  ::Cobweb::Key::D2
#define CW_KEY_3                  ::Cobweb::Key::D3
#define CW_KEY_4                  ::Cobweb::Key::D4
#define CW_KEY_5                  ::Cobweb::Key::D5
#define CW_KEY_6                  ::Cobweb::Key::D6
#define CW_KEY_7                  ::Cobweb::Key::D7
#define CW_KEY_8                  ::Cobweb::Key::D8
#define CW_KEY_9                  ::Cobweb::Key::D9
#define CW_KEY_SEMICOLON          ::Cobweb::Key::Semicolon  /* ; */
#define CW_KEY_EQUAL              ::Cobweb::Key::Equal  /* = */
#define CW_KEY_A                  ::Cobweb::Key::A
#define CW_KEY_B                  ::Cobweb::Key::B
#define CW_KEY_C                  ::Cobweb::Key::C
#define CW_KEY_D                  ::Cobweb::Key::D
#define CW_KEY_E                  ::Cobweb::Key::E
#define CW_KEY_F                  ::Cobweb::Key::F
#define CW_KEY_G                  ::Cobweb::Key::G
#define CW_KEY_H                  ::Cobweb::Key::H
#define CW_KEY_I                  ::Cobweb::Key::I
#define CW_KEY_J                  ::Cobweb::Key::J
#define CW_KEY_K                  ::Cobweb::Key::K
#define CW_KEY_L                  ::Cobweb::Key::L
#define CW_KEY_M                  ::Cobweb::Key::M
#define CW_KEY_N                  ::Cobweb::Key::N
#define CW_KEY_O                  ::Cobweb::Key::O
#define CW_KEY_P                  ::Cobweb::Key::P
#define CW_KEY_Q                  ::Cobweb::Key::Q
#define CW_KEY_R                  ::Cobweb::Key::R
#define CW_KEY_S                  ::Cobweb::Key::S
#define CW_KEY_T                  ::Cobweb::Key::T
#define CW_KEY_U                  ::Cobweb::Key::U
#define CW_KEY_V                  ::Cobweb::Key::V
#define CW_KEY_W                  ::Cobweb::Key::W
#define CW_KEY_X                  ::Cobweb::Key::X
#define CW_KEY_Y                  ::Cobweb::Key::Y
#define CW_KEY_Z                  ::Cobweb::Key::Z
#define CW_KEY_LEFT_BRACKET       ::Cobweb::Key::LeftBracket  /* [ */
#define CW_KEY_BACKSLASH          ::Cobweb::Key::BackSlash  /* \ */
#define CW_KEY_RIGHT_BRACKET      ::Cobweb::Key::RightBracket  /* ] */
#define CW_KEY_GRAVE_ACCENT       ::Cobweb::Key::GraveAccent  /* ` */
#define CW_KEY_WORLD_1            ::Cobweb::Key::World1 /* non-US #1 */
#define CW_KEY_WORLD_2            ::Cobweb::Key::World2 /* non-US #2 */

/* Function keys */
#define CW_KEY_ESCAPE             ::Cobweb::Key::Escape
#define CW_KEY_ENTER              ::Cobweb::Key::Enter
#define CW_KEY_TAB                ::Cobweb::Key::Tab
#define CW_KEY_BACKSPACE          ::Cobweb::Key::Backspace
#define CW_KEY_INSERT             ::Cobweb::Key::Insert
#define CW_KEY_DELETE             ::Cobweb::Key::Delete
#define CW_KEY_RIGHT              ::Cobweb::Key::Right
#define CW_KEY_LEFT               ::Cobweb::Key::Left
#define CW_KEY_DOWN               ::Cobweb::Key::Down
#define CW_KEY_UP                 ::Cobweb::Key::Up
#define CW_KEY_PAGE_UP            ::Cobweb::Key::PageUp
#define CW_KEY_PAGE_DOWN          ::Cobweb::Key::PageDown
#define CW_KEY_HOME               ::Cobweb::Key::Home
#define CW_KEY_END                ::Cobweb::Key::End
#define CW_KEY_CAPS_LOCK          ::Cobweb::Key::CapsLock
#define CW_KEY_SCROLL_LOCK        ::Cobweb::Key::ScrollLock
#define CW_KEY_NUM_LOCK           ::Cobweb::Key::NumLock
#define CW_KEY_PRINT_SCREEN       ::Cobweb::Key::PrintScreen
#define CW_KEY_PAUSE              ::Cobweb::Key::Pause
#define CW_KEY_F1                 ::Cobweb::Key::F1
#define CW_KEY_F2                 ::Cobweb::Key::F2
#define CW_KEY_F3                 ::Cobweb::Key::F3
#define CW_KEY_F4                 ::Cobweb::Key::F4
#define CW_KEY_F5                 ::Cobweb::Key::F5
#define CW_KEY_F6                 ::Cobweb::Key::F6
#define CW_KEY_F7                 ::Cobweb::Key::F7
#define CW_KEY_F8                 ::Cobweb::Key::F8
#define CW_KEY_F9                 ::Cobweb::Key::F9
#define CW_KEY_F10                ::Cobweb::Key::F10
#define CW_KEY_F11                ::Cobweb::Key::F11
#define CW_KEY_F12                ::Cobweb::Key::F12
#define CW_KEY_F13                ::Cobweb::Key::F13
#define CW_KEY_F14                ::Cobweb::Key::F14
#define CW_KEY_F15                ::Cobweb::Key::F15
#define CW_KEY_F16                ::Cobweb::Key::F16
#define CW_KEY_F17                ::Cobweb::Key::F17
#define CW_KEY_F18                ::Cobweb::Key::F18
#define CW_KEY_F19                ::Cobweb::Key::F19
#define CW_KEY_F20                ::Cobweb::Key::F20
#define CW_KEY_F21                ::Cobweb::Key::F21
#define CW_KEY_F22                ::Cobweb::Key::F22
#define CW_KEY_F23                ::Cobweb::Key::F23
#define CW_KEY_F24                ::Cobweb::Key::F24
#define CW_KEY_F25                ::Cobweb::Key::F25
#define CW_KEY_KP_0               ::Cobweb::Key::KP0
#define CW_KEY_KP_1               ::Cobweb::Key::KP1
#define CW_KEY_KP_2               ::Cobweb::Key::KP2
#define CW_KEY_KP_3               ::Cobweb::Key::KP3
#define CW_KEY_KP_4               ::Cobweb::Key::KP4
#define CW_KEY_KP_5               ::Cobweb::Key::KP5
#define CW_KEY_KP_6               ::Cobweb::Key::KP6
#define CW_KEY_KP_7               ::Cobweb::Key::KP7
#define CW_KEY_KP_8               ::Cobweb::Key::KP8
#define CW_KEY_KP_9               ::Cobweb::Key::KP9
#define CW_KEY_KP_DECIMAL         ::Cobweb::Key::KPDecimal
#define CW_KEY_KP_DIVIDE          ::Cobweb::Key::KPDivide
#define CW_KEY_KP_MULTIPLY        ::Cobweb::Key::KPMultiply
#define CW_KEY_KP_SUBTRACT        ::Cobweb::Key::KPSubtract
#define CW_KEY_KP_ADD             ::Cobweb::Key::KPAdd
#define CW_KEY_KP_ENTER           ::Cobweb::Key::KPEnter
#define CW_KEY_KP_EQUAL           ::Cobweb::Key::KPEqual
#define CW_KEY_LEFT_SHIFT         ::Cobweb::Key::LeftShift
#define CW_KEY_LEFT_CONTROL       ::Cobweb::Key::LeftControl
#define CW_KEY_LEFT_ALT           ::Cobweb::Key::LeftAlt
#define CW_KEY_LEFT_SUPER         ::Cobweb::Key::LeftSuper
#define CW_KEY_RIGHT_SHIFT        ::Cobweb::Key::RightShift
#define CW_KEY_RIGHT_CONTROL      ::Cobweb::Key::RightControl
#define CW_KEY_RIGHT_ALT          ::Cobweb::Key::RightAlt
#define CW_KEY_RIGHT_SUPER        ::Cobweb::Key::RightSuper
#define CW_KEY_MENU               ::Cobweb::Key::Menu

#define CW_KEY_LAST               ::Cobweb::Key::Last

#define CW_MOUSE_BUTTON_1         ::Cobweb::Button::Button1
#define CW_MOUSE_BUTTON_2         ::Cobweb::Button::Button2
#define CW_MOUSE_BUTTON_3         ::Cobweb::Button::Button3
#define CW_MOUSE_BUTTON_4         ::Cobweb::Button::Button4
#define CW_MOUSE_BUTTON_5         ::Cobweb::Button::Button5
#define CW_MOUSE_BUTTON_6         ::Cobweb::Button::Button6
#define CW_MOUSE_BUTTON_7         ::Cobweb::Button::Button7
#define CW_MOUSE_BUTTON_8         ::Cobweb::Button::Button8
#define CW_MOUSE_BUTTON_LAST      ::Cobweb::Button::Last
#define CW_MOUSE_BUTTON_LEFT      ::Cobweb::Button::Left
#define CW_MOUSE_BUTTON_RIGHT     ::Cobweb::Button::Right
#define CW_MOUSE_BUTTON_MIDDLE    ::Cobweb::Button::Middle
