#pragma once

extern Cobweb::Application *Cobweb::CreateApplication();

int main(int argc, char **argv)
{
	Cobweb::Application *app = Cobweb::CreateApplication();
	app->Run();
	delete app;
}
