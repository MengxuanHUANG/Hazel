#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include<glm/gtc/matrix_transform.hpp>

#include<glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController((2048.0f / 1080.0f), true)
{
}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture_2 = Hazel::Texture2D::Create("assets/textures/test_texture.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hazel::Timestep timestep)
{
	HZ_PROFILE_FUNCTION();

	//Updata Camera
	{
		HZ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdata(timestep);
	}

	//Set BackGround Color
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	//Start a new Scene
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Rotation, m_Texture_2);
	//Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, 0.0f, m_Texture, 10.0f);

	//End the Scene
	Hazel::Renderer2D::EndScene();
	
}

void Sandbox2D::OnImGuiRender(float timestep)
{
	ImGui::Begin("Settings");
	ImGui::SetWindowFontScale(2.0f);
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, result.Name);
		strcat(label, "  %.3fms");
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

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

	ImGui::Begin("Rotation");
	ImGui::SetWindowFontScale(2.0f);

	ImGui::SliderFloat("Rotation", &m_Rotation, 0, 360);
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);
}