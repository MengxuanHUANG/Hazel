#include "HZpch.h"

#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Hazel
{
	Scope<RenderAPI> RenderAPI::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return CreateScope<OpenGLRenderAPI>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}