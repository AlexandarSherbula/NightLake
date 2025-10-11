#pragma once

#include "Renderer/RendererBackend.hpp"

namespace aio
{
	class OpenGL_Backend : public RendererBackend
	{
	public:
		OpenGL_Backend();
		~OpenGL_Backend();

		void Init() override;
		void SetViewport(const Vector2& position, const Vector2& size) override;
		void Draw(uint32_t vertexCount) override;
		void DrawIndexed(uint32_t indexCount) override;
		void Clear(const Vector4& color) override;

		inline std::string GetName() const override { return "OpenGL 4.5"; };
	private:
		static OpenGL_Backend* sInstance;
	};
}