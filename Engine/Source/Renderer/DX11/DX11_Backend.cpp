#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)
#include "DX11_Backend.hpp"

#include "Core/Application.hpp"

namespace aio
{
	std::string GetVendorName(UINT vendorId)
	{
		switch (vendorId)
		{
		case 0x10DE: return "NVIDIA Corporation";
		case 0x1002: return "AMD";
		case 0x8086: return "Intel";
		case 0x1414: return "Microsoft";
		default:     return "Unknown Vendor";
		}
	}

	std::string GetFeatureLevelString(D3D_FEATURE_LEVEL level)
	{
		switch (level)
		{
		case D3D_FEATURE_LEVEL_12_1: return "12.1";
		case D3D_FEATURE_LEVEL_12_0: return "12.0";
		case D3D_FEATURE_LEVEL_11_1: return "11.1";
		case D3D_FEATURE_LEVEL_11_0: return "11.0";
		case D3D_FEATURE_LEVEL_10_1: return "10.1";
		case D3D_FEATURE_LEVEL_10_0: return "10.0";
		default: return "Unknown";
		}
	}

	DX11_Backend::DX11_Backend()
	{
	}

	DX11_Backend::~DX11_Backend()
	{
	}

	void DX11_Backend::Init()
	{
		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetWindow()->GetContext());

		mDevice = mContext->GetDevice();
		mDeviceContext = mContext->GetDeviceContext();

		// Get adapter info
		IDXGIAdapter* adapter = nullptr;

		IDXGIFactory* pFactory = nullptr;
		AIO_ASSERT(SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory)), "Failed to create DXGI Factory");

		if (SUCCEEDED(pFactory->EnumAdapters(0, &adapter)))
		{
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);

			AIO_LOG_INFO("DirectX 11 Info:");
			AIO_LOG_INFO(" Vendor: {0}", GetVendorName(desc.VendorId));
			AIO_LOG_INFO(" Renderer: {0}", WideToString(desc.Description).c_str());
			AIO_LOG_INFO(" Version: Direct3D {0}", GetFeatureLevelString(mContext->GetFeatureLevel()));

			adapter->Release();
		}

		pFactory->Release();
	}

	void DX11_Backend::SetViewport(const Vector2& position, const Vector2& size)
	{
		mContext->ResizeBuffer(size);
	}

	void DX11_Backend::Draw(uint32_t vertexCount)
	{
		mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		mDeviceContext->Draw(vertexCount, 0);
	}

	void DX11_Backend::DrawIndexed(uint32_t indexCount)
	{
		mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mDeviceContext->DrawIndexed(indexCount, 0, 0);
	}

	void DX11_Backend::Clear(const Vector4& color)
	{
		mContext->ClearRenderTargetView(color);
		mContext->SetRenderTarget();
	}

}
#endif