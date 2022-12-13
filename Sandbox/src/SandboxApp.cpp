#include<Hazal.h>

class Sandbox : public Hazal::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Hazal::Application* Hazal::CreateApplication()
{
	return new Sandbox();
}