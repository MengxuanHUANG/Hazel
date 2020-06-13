#pragma once
#include<Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();
	~ExampleLayer() = default;
	void OnUpdate(Hazel::Timestep timestep) override;
	void OnImGuiRender(float timestep) override;
	void OnEvent(Hazel::Event& event) override;
	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event);

private:
	Hazel::ShaderLib m_ShaderLib;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_BlueShader;
	Hazel::Ref<Hazel::VertexArray> m_Square_VertexArray;

	Hazel::Ref<Hazel::Texture2D> m_LogoTexture;
	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_BackGroundColor = { 0.1f, 0.1f, 0.1f };

	std::string m_FPS;
	unsigned int m_Count = 0;
};