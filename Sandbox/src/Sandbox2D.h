#pragma once

#include<Hazel.h>

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach()override;
	virtual void OnDetach()override;

	virtual void OnUpdate(Hazel::Timestep timestep)override;
	virtual void OnImGuiRender(float timestep)override;
	virtual void OnEvent(Hazel::Event& event)override;

private:
	Hazel::OrthographicCameraController m_CameraController;

	//Temp
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::Shader> m_Shader;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	std::string m_FPS;
	unsigned int m_Count = 0;
};