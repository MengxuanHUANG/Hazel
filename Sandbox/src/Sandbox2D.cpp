#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include<glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/Renderer/OpenGLShader.h"
#include<glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController((2048.0f / 1080.0f), true)
{
}

void Sandbox2D::OnAttach()
{
	m_VertexArray = Hazel::VertexArray::Create();
	float square[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	m_VertexArray = Hazel::VertexArray::Create();
	Hazel::Ref<Hazel::VertexBuffer> squareVB;
	squareVB.reset(Hazel::VertexBuffer::Create(square, sizeof(square)));

	Hazel::BufferLayout layout = {
		{ Hazel::ShaderDataType::Float3, "a_Position" }
	};
	squareVB->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> squareIB;
	squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_VertexArray->AddIndexBuffer(squareIB);

	m_Shader = Hazel::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hazel::Timestep timestep)
{
	//Updata Camera
	m_CameraController.OnUpdata(timestep);

	//Set BackGround Color
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	//Start a new Scene
	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

	Hazel::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//End the Scene
	Hazel::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender(float timestep)
{
	ImGui::Begin("Settings");
	ImGui::SetWindowFontScale(2.0f);
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

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

void Sandbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);
}
