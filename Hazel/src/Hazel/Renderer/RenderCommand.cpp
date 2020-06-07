#include "HZpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Hazel
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}