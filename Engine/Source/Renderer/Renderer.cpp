#include "aio_pch.hpp"

#include "Renderer.hpp"

namespace aio
{
	GraphicsAPI Renderer::sAPI = OpenGL;
	Scope<RendererBackend> Renderer::sBackend = nullptr;

	void Renderer::Init()
	{
		sBackend = RendererBackend::Create();
		sBackend->Init();
	}

	void Renderer::Draw()
	{
		sBackend->Clear(Vector4(0.0f, 0.8f, 1.0f, 1.0f));
		sBackend->DrawIndexed(6);
	}

	void Renderer::SetAPI(GraphicsAPI api)
	{
#if defined (AIO_WINDOWS)
		sAPI = api;
#endif
	}

	void Renderer::OnWindowResize(WindowResizeEvent& e)
	{
		if (sBackend != nullptr)
			sBackend->SetViewport(Vector2(0.0f, 0.0f), Vector2(e.GetWidth(), e.GetHeight()));
	}
}