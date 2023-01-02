#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazal {

	class HAZAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}