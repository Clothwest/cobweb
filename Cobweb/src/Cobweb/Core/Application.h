#pragma once

#include "Core.h"

namespace Cobweb
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To bo defined in CLIENT
	Application *CreateApplication();
}

