#include <Hazal.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hazal::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hazal::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Hazal::VertexBuffer> vertexBuffer;
		std::shared_ptr<Hazal::IndexBuffer> indexBuffer;
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

		m_SquareVA.reset(Hazal::VertexArray::Create());

		float square_vertices[] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Hazal::VertexBuffer> squareVB;
		squareVB.reset(Hazal::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		squareVB->SetLayout({
			{ Hazal::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<Hazal::IndexBuffer> squareIB;
		squareIB.reset(Hazal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}

		)";

		m_Shader.reset(new Hazal::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";
		m_Shader2.reset(new Hazal::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(Hazal::Timestep ts) override
	{
		if (Hazal::Input::IsKeyPressed(HAZAL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hazal::Input::IsKeyPressed(HAZAL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Hazal::Input::IsKeyPressed(HAZAL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Hazal::Input::IsKeyPressed(HAZAL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hazal::Input::IsKeyPressed(HAZAL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Hazal::Input::IsKeyPressed(HAZAL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Hazal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazal::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazal::Renderer::BeginScene(m_Camera);

		Hazal::Renderer::Submit(m_Shader2, m_SquareVA);
		Hazal::Renderer::Submit(m_Shader, m_VertexArray);

		Hazal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Hazal::Event& event) override
	{

	}
private:
	std::shared_ptr<Hazal::Shader> m_Shader;
	std::shared_ptr<Hazal::Shader> m_Shader2;

	std::shared_ptr<Hazal::VertexArray> m_VertexArray;
	std::shared_ptr<Hazal::VertexArray> m_SquareVA;

	Hazal::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;
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