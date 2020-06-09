#pragma once

#include "Renderer.h"
#include "VertexArray.h"
#include <glm/glm.hpp>

namespace Hazel
{
	class RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray)  = 0;
	};
}
