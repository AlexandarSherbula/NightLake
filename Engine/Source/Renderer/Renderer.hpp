#pragma once

#include "Utils/Math.hpp"

#include "RendererBackend.hpp"
#include "GraphicsContext.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "Events/WindowEvent.hpp"

enum GraphicsAPI
{
	OpenGL,
	DX11
};

#if defined(AIO_WINDOWS)

#define CHECK_API(x, y)                                                    \
        do {                                                               \
            switch (aio::Renderer::GetAPI())                               \
            {                                                              \
                case OpenGL: { x; break; }                                 \
                case DX11:   { y; break; }                                 \
                default:     { AIO_ASSERT(false, "Unknown API."); break; } \
            }                                                              \
        } while(0)
#else
#define CHECK_API(x, y) do { x; } while(0)
#endif


namespace aio
{
	class Renderer
	{
	public:
		static void Init();
		static void Draw();

		static void SetAPI(GraphicsAPI api);
		static void OnWindowResize(WindowResizeEvent& e);

		inline static const Scope<RendererBackend>& Backend() { return sBackend; }
		inline static const GraphicsAPI GetAPI() { return sAPI; }

	private:
		static GraphicsAPI sAPI;
		static Scope<RendererBackend> sBackend;
	};
}