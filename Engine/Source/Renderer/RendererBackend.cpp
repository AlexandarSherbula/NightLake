#include "aio_pch.hpp"
#include "RendererBackend.hpp"

#include "OpenGL/OpenGL_Backend.hpp"
#include "DX11/DX11_Backend.hpp"

#include "Renderer/Renderer.hpp"

namespace aio
{
	Scope<RendererBackend> RendererBackend::Create()
	{
		CHECK_API
		(
			return CreateScope<OpenGL_Backend>(),
			return CreateScope<DX11_Backend>()
		);
		return nullptr;
	}

}
