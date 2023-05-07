#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Hazal::VertexArray::Create();

	float square_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Hazal::Ref<Hazal::VertexBuffer> squareVB;
	squareVB.reset(Hazal::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
	squareVB->SetLayout({
		{ Hazal::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[] = {
		0, 1, 2,
		2, 3, 0
	};
	Hazal::Ref<Hazal::IndexBuffer> squareIB;
	squareIB.reset(Hazal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);
	
	m_FlatColorShader = Hazal::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazal::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazal::RenderCommand::Clear();

	Hazal::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Hazal::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazal::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazal::Event& e)
{
	m_CameraController.OnEvent(e);
}
