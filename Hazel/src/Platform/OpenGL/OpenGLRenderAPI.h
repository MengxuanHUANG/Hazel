#pragma once

#include "Hazel/Renderer/RenderAPI.h"

namespace Hazel
{
	class OpenGLRenderAPI :public RenderAPI
	{
	public:
		OpenGLRenderAPI() {}
		~OpenGLRenderAPI() {}

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}