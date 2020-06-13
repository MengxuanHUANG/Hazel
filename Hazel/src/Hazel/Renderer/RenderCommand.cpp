#include "HZpch.h"
#include "RenderCommand.h"

namespace Hazel
{
	Scope<RenderAPI> RenderCommand::s_RenderAPI = RenderAPI::Create();
}