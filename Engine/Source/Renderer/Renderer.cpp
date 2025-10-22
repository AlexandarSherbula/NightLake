#include "aio_pch.hpp"

#include "Renderer.hpp"

namespace aio
{
	GraphicsAPI Renderer::sAPI = OpenGL;
	Scope<RendererBackend> Renderer::sBackend = nullptr;
	ShaderLibrary Renderer::sShaderLibrary;

	void Renderer::Init()
	{
		sBackend = RendererBackend::Create();
		sBackend->Init();
	}

	void Renderer::Draw()
	{
		sBackend->Clear(Vector4(0.1f, 0.1f, 0.1f, 1.0f));
		sBackend->DrawIndexed(6);
	}

	void Renderer::SetAPI(GraphicsAPI api)
	{
#if defined (AIO_WINDOWS)
		sAPI = api;
#endif
	}
}