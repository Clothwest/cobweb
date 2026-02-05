#pragma once

extern Cobweb::Application *Cobweb::CreateApplication();

int main(int argc, char **argv)
{
	Cobweb::Log::Init();
	CW_CORE_INFO("Log initialized!");

	int a = 5;
	CW_CORE_WARN("a is {}.", a);
	CW_ERROR("a is {}.", a);

	CW_ASSERT(false, "a is {}!", a);

	Cobweb::Application *app = Cobweb::CreateApplication();
	app->Run();
	delete app;
}
