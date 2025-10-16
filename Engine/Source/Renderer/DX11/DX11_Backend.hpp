#pragma once

#include "Renderer/RendererBackend.hpp"

#if defined (AIO_WINDOWS)
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

#include "DX11_Context.hpp"

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

		inline std::string GetName() const override { return "DirectX 11"; }
	private:
		static DX11_Backend* sInstance;
	private:
		Ref<DX11_Context> mContext;
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
	};
}
#else
namespace aio
{
	class DX11_Backend : public RendererBackend
	{
	public:
		DX11_Backend() {}
		~DX11_Backend() {}

		void Init() override {}
		void SetViewport(const Vector2& position, const Vector2& size) override {}
		void Draw(uint32_t vertexCount) override                                {}
		void DrawIndexed(uint32_t indexCount) override                          {}
		void Clear(const Vector4& color) override                               {}
		inline std::string GetName() const override                 { return ""; }
	private:
		static DX11_Backend* sInstance;
	};
}
#endif
