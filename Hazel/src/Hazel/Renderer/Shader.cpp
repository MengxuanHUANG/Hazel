#include "HZpch.h"

#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/Renderer/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is not support!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}