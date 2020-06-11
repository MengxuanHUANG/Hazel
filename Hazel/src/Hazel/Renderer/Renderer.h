#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"
#include "Hazel/Camera/OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		static void Flush();

		static inline RendererAPI GetRendererAPI() { return s_SceneData->s_RendererAPI; }
	private:

		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
			RendererAPI s_RendererAPI = RendererAPI::OpenGL;
		};

		static SceneData* s_SceneData;
	};
}