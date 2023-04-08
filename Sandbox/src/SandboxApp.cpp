#include <Hazal.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

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

		m_SquareVA.reset(Hazal::VertexArray::Create());

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

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader.reset(Hazal::Shader::Create(vertexSrc, fragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}

		)";
		m_TextureShader.reset(Hazal::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Hazal::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		// std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_Shader2)->Bind();
		// std::dynamic_pointer_cast<Hazal::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

		/*for (int i = 0; i < 20; ++i)
			for (int j = 0; j < 20; ++j)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazal::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}*/
		
		m_Texture->Bind();
		Hazal::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Hazal::Renderer::Submit(m_Shader, m_VertexArray);

		Hazal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazal::Event& event) override
	{

	}
private:
	Hazal::Ref<Hazal::Shader> m_Shader;
	Hazal::Ref<Hazal::Shader> m_TextureShader;

	Hazal::Ref<Hazal::VertexArray> m_VertexArray;
	Hazal::Ref<Hazal::VertexArray> m_SquareVA;

	Hazal::Ref<Hazal::Texture2D> m_Texture;

	Hazal::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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