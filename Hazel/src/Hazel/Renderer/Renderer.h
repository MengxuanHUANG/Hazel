#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"

namespace Hazel
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static void Flush();

		static inline RendererAPI GetRendererAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}