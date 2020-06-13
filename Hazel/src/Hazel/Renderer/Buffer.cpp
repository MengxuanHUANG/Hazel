#include "HZpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t sizes)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None :
			HZ_CORE_ASSERT(false, "RendererAPI::None is not support!");
			return nullptr;
		case RendererAPI::OpenGL :
			return CreateRef<OpenGLVertexBuffer>(vertices, sizes);
		default:
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* vertices, uint32_t count)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is not support!");
			return nullptr;
		case RendererAPI::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(vertices, count);
		default:
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}