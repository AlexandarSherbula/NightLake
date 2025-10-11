#pragma once

#include "Utils/Math.hpp"

#include "Renderer/RendererBackend.hpp"
#include "Renderer/GraphicsContext.hpp"

enum GraphicsAPI
{
	OpenGL,
	DX11
};

namespace aio
{
	class Renderer
	{
	public:
		static void Init();
		static void Draw();

		static void SetAPI(GraphicsAPI api);

		inline static Scope<RendererBackend>& Backend() { return sBackend; }
		inline static GraphicsAPI GetAPI() { return sAPI; }
	private:
		static Scope<RendererBackend> sBackend;
		static GraphicsAPI sAPI;
	};
}