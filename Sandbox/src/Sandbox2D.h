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

	Hazel::Ref<Hazel::Texture2D> m_Texture;
	Hazel::Ref<Hazel::Texture2D> m_Texture_2;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	float m_Rotation = 0.0f;

	std::string m_FPS;
	unsigned int m_Count = 0;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};