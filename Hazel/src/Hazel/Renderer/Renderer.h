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

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

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