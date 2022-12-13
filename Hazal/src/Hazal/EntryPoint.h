#pragma once

#ifdef HAZAL_PLATFORM_WINDOWS

extern Hazal::Application* Hazal::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Hazal::CreateApplication();
	app->Run();
	delete app;
}
#endif