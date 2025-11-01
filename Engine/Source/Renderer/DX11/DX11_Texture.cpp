#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)
#include "DX11_Texture.hpp"
#include "Core/Application.hpp"
#include "stb_image.hpp"

#include "Utils/FileReading.hpp"

namespace aio
{
	uint32_t DX11_Texture::sID = 1;

	DX11_Texture::DX11_Texture(uint32_t width, uint32_t height)
	{
		mID = sID;

		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.BorderColor[0] = 0;
		sampDesc.BorderColor[1] = 0;
		sampDesc.BorderColor[2] = 0;
		sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		HRESULT hr = mContext->GetDevice()->CreateSamplerState(&sampDesc, mSamplerState.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create sampler state: " + ResultInfo(hr) + "\n");

		ID3D11Texture2D* textureObject;
		ZeroMemory(&textureObject, sizeof(textureObject));

		uint32_t whiteTexture = 0xffffffff;

		D3D11_SUBRESOURCE_DATA textureSubData;
		ZeroMemory(&textureSubData, sizeof(textureSubData));
		textureSubData.pSysMem = &whiteTexture;
		textureSubData.SysMemPitch = width * 4;

		hr = mContext->GetDevice()->CreateTexture2D(&textureDesc, &textureSubData, mTextureBuffer.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create white texture: " + ResultInfo(hr) + "\n");

		hr = mContext->GetDevice()->CreateShaderResourceView(mTextureBuffer.Get(), nullptr, mTextureResource.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create texture shader resource view: " + ResultInfo(hr) + "\n");
		sID++;
	}

	DX11_Texture::DX11_Texture(const std::string& filepath, std::string name)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		if (data)
		{
			mName = name;
			mWidth = width;
			mHeight = height;
			mID = sID;

			D3D11_TEXTURE2D_DESC textureDesc;
			ZeroMemory(&textureDesc, sizeof(textureDesc));

			textureDesc.Width = mWidth;
			textureDesc.Height = mHeight;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			D3D11_SAMPLER_DESC sampDesc;
			ZeroMemory(&sampDesc, sizeof(sampDesc));

			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.MipLODBias = 0.0f;
			sampDesc.MaxAnisotropy = 1;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.BorderColor[0] = 0;
			sampDesc.BorderColor[1] = 0;
			sampDesc.BorderColor[2] = 0;
			sampDesc.BorderColor[3] = 0;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

			HRESULT hr = mContext->GetDevice()->CreateSamplerState(&sampDesc, mSamplerState.GetAddressOf());
			AIO_ASSERT(SUCCEEDED(hr), "Failed to create sampler state: " + ResultInfo(hr) + "\n");

			D3D11_SUBRESOURCE_DATA textureSubData;
			ZeroMemory(&textureSubData, sizeof(textureSubData));
			textureSubData.pSysMem = data;
			textureSubData.SysMemPitch = mWidth * channels;

			Microsoft::WRL::ComPtr<ID3D11Texture2D> textureObject;
			hr = mContext->GetDevice()->CreateTexture2D(&textureDesc, &textureSubData, &textureObject);
			AIO_ASSERT(SUCCEEDED(hr), "Failed to create a texture: " + ResultInfo(hr) + "\n");

			hr = mContext->GetDevice()->CreateShaderResourceView(textureObject.Get(), nullptr, mTextureResource.GetAddressOf());
			AIO_ASSERT(SUCCEEDED(hr), "Failed to create texture shader resource view: " + ResultInfo(hr) + "\n");
			sID++;
		}
	}

	DX11_Texture::~DX11_Texture()
	{
	}

	void DX11_Texture::Bind(uint32_t slot) const
	{
		mContext->GetDeviceContext()->PSSetSamplers(slot, 1, mSamplerState.GetAddressOf());
		mContext->GetDeviceContext()->PSSetShaderResources(slot, 1, mTextureResource.GetAddressOf());
	}

	void DX11_Texture::Unbind() const
	{
	}

	void DX11_Texture::SetData(const void* data, uint32_t size)
	{
	}
}
#endif