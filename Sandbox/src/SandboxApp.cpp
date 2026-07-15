#include <Cobweb.h>
#include <Cobweb/EntryPoint.h>

#include "SandboxLayer.h"
#include "Sandbox2DLayer.h"

class SandboxApp : public Cobweb::Application
{
public:
	SandboxApp()
	{
		//PushLayer(new SandboxLayer());
		PushLayer(new Sandbox2DLayer());
	}

	~SandboxApp() = default;

private:

};

Cobweb::Application *Cobweb::CreateApplication()
{
	return new SandboxApp();
}
