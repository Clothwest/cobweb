#include <Cobweb.h>
#include <Cobweb/Core/EntryPoint.h>

#include "SandboxLayer.h"

class SandboxApp : public Cobweb::Application
{
public:
	SandboxApp()
	{
		PushLayer(new SandboxLayer());
	}

	~SandboxApp() = default;

private:

};

Cobweb::Application *Cobweb::CreateApplication()
{
	return new SandboxApp();
}
