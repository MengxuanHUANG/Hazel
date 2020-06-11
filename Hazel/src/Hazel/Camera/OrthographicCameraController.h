#pragma once

#include "OrthographicCamera.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/MouseEvent.h"

namespace Hazel
{
	class Timestep;

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRation, bool rotaionEnable);

		void OnUpdata(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f, m_CameraRotatedSpeed = 180.0f;
	};
}