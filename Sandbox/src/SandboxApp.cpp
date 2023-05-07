#include <Hazal.h>
#include <Hazal/Core/EntryPoint.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Hazal::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Hazal::VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Hazal::Ref<Hazal::VertexBuffer> vertexBuffer;
		Hazal::Ref<Hazal::IndexBuffer> indexBuffer;
		vertexBuffer.reset(Hazal:: VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazal::BufferLayout layout = {
			{ Hazal::ShaderDataType::Float3, "a_Position", true},
			{ Hazal::ShaderDataType::Float4, "a_Color", true },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = {
			0, 1, 2
		};
		indexBuffer.reset(Hazal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Hazal::VertexArray::Create();

		float square_vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazal::Ref<Hazal::VertexBuffer> squareVB;
		squareVB.reset(Hazal::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		squareVB->SetLayout({
			{ Hazal::ShaderDataType::Float3, "a_Position" },
			{ Hazal::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};
		Hazal::Ref<Hazal::IndexBuffer> squareIB;
		squareIB.reset(Hazal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Hazal::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Hazal::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hazal::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hazal::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hazal::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Hazal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazal::RenderCommand::Clear();

		Hazal::Renderer::BeginScene(m_CameraController.GetCamera());
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Hazal::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Hazal::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Hazal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazal::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Hazal::ShaderLibrary m_ShaderLibrary;

	Hazal::Ref<Hazal::VertexArray> m_VertexArray;
	Hazal::Ref<Hazal::VertexArray> m_SquareVA;

	Hazal::Ref<Hazal::Texture2D> m_Texture;
	Hazal::Ref<Hazal::Texture2D> m_ChernoLogoTexture;

	Hazal::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hazal::Application
{
public:
	Sandbox()
	{
		// PushLayer(new(ExampleLayer));
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Hazal::Application* Hazal::CreateApplication()
{
	return new Sandbox();
}