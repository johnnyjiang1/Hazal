#pragma once

#include "Hazal.h"

class Sandbox2D : public Hazal::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazal::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazal::Event& e) override;
private:
	Hazal::OrthographicCameraController m_CameraController;

	Hazal::Ref<Hazal::VertexArray> m_SquareVA;
	Hazal::Ref<Hazal::Shader>  m_FlatColorShader;

	Hazal::Ref<Hazal::Texture2D> m_CheckerBoardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};