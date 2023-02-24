#include <Hazal.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hazal::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		// HAZAL_CLIENT_INFO("ExampleLayer::Update");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Hazal::Event& event) override
	{
		// HAZAL_CLIENT_TRACE("{0}", event);
		if (event.GetEventType() == Hazal::EventType::KeyPressed)
		{
			Hazal::KeyPressedEvent& e = (Hazal::KeyPressedEvent&)event;
			HAZAL_CORE_TRACE("{0}", (char) e.GetKeyCode());
		}
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