#include "Application.h"

#include "Cobweb/Events/Events.h"

namespace Cobweb
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowClosedEvent windowClosed;
		CW_CORE_TRACE(windowClosed);

		WindowResizedEvent windowResized(1920, 1080);
		CW_CORE_TRACE(windowResized);

		KeyPressedEvent keyPressed(65, 0);
		CW_CORE_TRACE(keyPressed);

		MouseButtonPressedEvent mouseButtonPressed(1);
		CW_CORE_TRACE(mouseButtonPressed);

		MouseScrolledEvent mouseScrolled(0, 1);
		CW_CORE_TRACE(mouseScrolled);

		KeyReleasedEvent keyReleased(65);
		if (keyReleased.IsInCategory(EventCategory_Input))
		{
			CW_CORE_TRACE(keyReleased);
		}

		while (true)
		{

		}
	}
}
