#pragma once

#include "Utils/Math.hpp"

#include "RendererBackend.hpp"
#include "GraphicsContext.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include "Events/WindowEvent.hpp"

enum class GraphicsAPI
{
	OpenGL,
	DX11
};

#if defined(AIO_WINDOWS)

#define CHECK_API(x, y)                                                    \
        do {                                                               \
            switch (aio::Renderer::CheckAPI())                             \
            {                                                              \
                case GraphicsAPI::OpenGL: { x; break; }                    \
                case GraphicsAPI::DX11:   { y; break; }                    \
                default:     { AIO_ASSERT(false, "Unknown API."); break; } \
            }                                                              \
        } while(0)
#define SET_API(x) aio::Renderer::SetAPI(x)
#else
#define CHECK_API(x, y) do { x; } while(0)
#define SET_API(x)
#endif


namespace aio
{
	class Renderer
	{
	public:
		static void Init();
		static void Draw();

		static void OnWindowResize(WindowResizeEvent& e);

		inline static const Scope<RendererBackend>& Backend() { return sBackend; }
		inline static const GraphicsAPI CheckAPI() { return sAPI; }
#if defined (AIO_WINDOWS)
		inline static void SetAPI(GraphicsAPI api) { sAPI = api; }
#endif
	private:
		static GraphicsAPI sAPI;
		static Scope<RendererBackend> sBackend;
	};
}