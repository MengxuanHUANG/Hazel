#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotaion() const { return m_Rotation; }

		void SetPostion(const glm::vec3& position) 
		{ 
			m_Position = position; 
			ReCalculateViewMatrix();
		}
		void SetRotation(float rotation) 
		{ 
			m_Rotation = rotation; 
			ReCalculateViewMatrix();
		}

		const glm::mat4& GetProjMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMatrix; }

	private:
		void ReCalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
