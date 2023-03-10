#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazal {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: HAZAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		HAZAL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}