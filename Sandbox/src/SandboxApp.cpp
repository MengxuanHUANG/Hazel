#include<Hazel.h>

#include "imgui/imgui.h"

#include<glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/Renderer/OpenGLShader.h"
#include<glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController((2048.0f / 1080.0f), true)
	{
		//---------------------Triangle-------------------------
		{
			m_VertexArray.reset(Hazel::VertexArray::Create());
			float vertices[3 * 7] =
			{
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f, 0.5f, 0.0f,  0.8f, 0.8f, 0.2f, 1.0f
			};
			Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

			Hazel::BufferLayout layout = {
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			// Index Buffer
			uint32_t indices[3] = { 0, 1, 2 };
			Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->AddIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4  u_ViewProjection;
				uniform mat4  u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";
			std::string fragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);
				}
			)";

			m_Shader = Hazel::Shader::Create("TriangleShader", vertexSrc, fragmentSrc);
		}

		//---------------------test Square-----------------------
		{
			float square[5 * 4] =
			{
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			m_Square_VertexArray.reset(Hazel::VertexArray::Create());
			Hazel::Ref<Hazel::VertexBuffer> squareVB;
			squareVB.reset(Hazel::VertexBuffer::Create(square, sizeof(square)));

			Hazel::BufferLayout layout = {
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float2, "a_TextCoord" }
			};
			squareVB->SetLayout(layout);
			m_Square_VertexArray->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Hazel::Ref<Hazel::IndexBuffer> squareIB;
			squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_Square_VertexArray->AddIndexBuffer(squareIB);

			std::string blueVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4  u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";
			std::string blueFragmentSrc2 = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0);
				}
			)";

			m_BlueShader = Hazel::Shader::Create("SquareShader", blueVertexSrc, blueFragmentSrc2);
		}

		//--------------------Texture Shader---------------------
		{
			Hazel::Ref<Hazel::Shader> shader = m_ShaderLib.Load("assets/shaders/Texture.glsl");
			m_Texture = Hazel::Texture2D::Create("assets/textures/test_texture.png");
			//m_LogoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

			std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->Bind();
			std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->UploadUniformInt("u_Texture", 0);
		}
	}

	void OnUpdate(Hazel::Timestep timestep) override
	{
		float ts = timestep;
		m_CameraController.OnUpdata(ts);

		//Set BackGround Color
		Hazel::RenderCommand::SetClearColor(glm::vec4(m_BackGroundColor, 1.0f));
		Hazel::RenderCommand::Clear();

		//Start a new Scene
		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

		//++++++++++++++++++++Will be implement in the future++++++++++++++
		/*Hazel::Material* material = new Hazel::Material(m_FlatColorShader);
		material->Set("u_Color", redColor);

		squareMesh->SetMeterial(material);*/
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		//set up the Scale Matrix
		static glm::mat scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_BlueShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		//*********************Render the Square Matrix**********************
		/*for (int j = 0; j < 20; ++j)
		{
			for (int i = 0; i < 20; ++i)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Hazel::Renderer::Submit(m_BlueShader, m_Square_VertexArray, transform);
			}
		}*/

		//****************************Render the Image*************************
		auto TextureShader = m_ShaderLib.Get("Texture");
		m_Texture->Bind();
		Hazel::Renderer::Submit(TextureShader, m_Square_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//*************************Rendere the Logo***************************
		//m_LogoTexture->Bind();
		//Hazel::Renderer::Submit(m_TextureShader, m_Square_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//*********************Render the test Triangle************************
		//Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		//End the Scene
		Hazel::Renderer::EndScene();
		Hazel::Renderer::Flush();
	}

	void OnImGuiRender(float timestep) override
	{
		ImGui::Begin("Settings");
		ImGui::SetWindowFontScale(2.0f);
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_BackGroundColor));

		if ((m_Count++) % 10);
		else
		{
			std::stringstream ss;
			ss << "fps: " << 1.0f / timestep;
			m_FPS = ss.str();
			m_Count = 1;
		}

		ImGui::Text(m_FPS.c_str());
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{
		m_CameraController.OnEvent(event);

		if (event.GetEventType() == Hazel::EventType::WindowResize)
		{
			auto& re = (Hazel::WindowResizeEvent&) event;
		}
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event)
	{
		return false;
	}

private:
	Hazel::ShaderLib m_ShaderLib;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_BlueShader;
	Hazel::Ref<Hazel::VertexArray> m_Square_VertexArray;

	Hazel::Ref<Hazel::Texture2D> m_LogoTexture;
	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
	glm::vec3 m_BackGroundColor = { 0.1f, 0.1f, 0.1f };

	std::string m_FPS;
	unsigned int m_Count = 0;
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}