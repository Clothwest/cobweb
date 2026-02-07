#pragma once

extern Cobweb::Application *Cobweb::CreateApplication();

int main(int argc, char **argv)
{
	Cobweb::Log::Init();
	CW_CORE_INFO("Log initialized!");

	Cobweb::Application *app = Cobweb::CreateApplication();
	app->Run();
	delete app;
}
