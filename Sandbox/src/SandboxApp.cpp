#include<Hazal.h>

class ExampleLayer : public Hazal::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		HAZAL_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazal::Event& event) override
	{
		HAZAL_CLIENT_TRACE("{0}", event);
	}
};

class Sandbox : public Hazal::Application
{
public:
	Sandbox()
	{
		PushLayer(new(ExampleLayer));
	}

	~Sandbox()
	{

	}
};

Hazal::Application* Hazal::CreateApplication()
{
	return new Sandbox();
}