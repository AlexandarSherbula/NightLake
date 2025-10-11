#pragma once

#include "Renderer/RendererBackend.hpp"

namespace aio
{
	class DX11_Backend : public RendererBackend
	{
	public:
		DX11_Backend();
		~DX11_Backend();

		void Init() override;
		void SetViewport(const Vector2& position, const Vector2& size) override;
		void Draw(uint32_t vertexCount) override;
		void DrawIndexed(uint32_t indexCount) override;
		void Clear(const Vector4& color) override;

		void CreateRenderTarget();
		void CleanRenderTarget();
		void SetRenderTarget();
		inline std::string GetName() const override { return "DirectX 11"; }
	private:
		static DX11_Backend* sInstance;
	};
}
