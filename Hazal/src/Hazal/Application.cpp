#include"Application.h"

#include "Hazal/Events/ApplicationEvent.h"
#include "Hazal/Log.h"

namespace Hazal {

	Application::Application(){}

	Application::~Application(){}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HAZAL_CLIENT_TRACE(e);

		while (true);
	}

}