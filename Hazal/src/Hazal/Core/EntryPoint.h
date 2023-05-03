#pragma once

#ifdef HAZAL_PLATFORM_WINDOWS

extern Hazal::Application* Hazal::CreateApplication();

int main(int argc, char** argv)
{
	Hazal::Log::Init();
	HAZAL_CORE_WARN("Initialized Log!");
	HAZAL_CLIENT_INFO("Hello!");

	auto app = Hazal::CreateApplication();
	app->Run();
	delete app;
}
#endif