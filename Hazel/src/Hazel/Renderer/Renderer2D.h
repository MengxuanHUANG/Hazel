#pragma once

#include "glm/glm.hpp"
#include "Hazel/Camera/OrthographicCamera.h"

#include "Texture.h"

namespace Hazel
{

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		//Primitives

		//Pure Color
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		//Pure Texture
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
	private:
		inline static glm::mat4 GetTransform(const glm::vec3& position, const glm::vec2& size, float rotation);
	};
}