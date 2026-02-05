#include "Cobweb.h"

class SandboxApp : public Cobweb::Application
{
public:
	SandboxApp() = default;
	~SandboxApp() = default;
};

Cobweb::Application *Cobweb::CreateApplication()
{
	return new SandboxApp();
}
