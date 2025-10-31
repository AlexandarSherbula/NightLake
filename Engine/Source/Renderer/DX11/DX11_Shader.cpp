#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)

#include "DX11_Shader.hpp"
#include "Core/Application.hpp"

#include "Utils/FileReading.hpp"

namespace aio
{

	static DXGI_FORMAT DX11BaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShaderDataType::Int:      return DXGI_FORMAT_R32_SINT;
		case ShaderDataType::Int2:     return DXGI_FORMAT_R32G32_SINT;
		case ShaderDataType::Int3:     return DXGI_FORMAT_R32G32B32_SINT;
		case ShaderDataType::Int4:     return DXGI_FORMAT_R32G32B32A32_SINT;
		}

		AIO_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT_UNKNOWN;
	}


	DX11_Shader::DX11_Shader(const std::string& name, const Ref<VertexInput>& vertexInput)
	{
		mName = name;
		mVertexSource = mPixelSource = GetProjectDirectory() + "Sandbox/Assets/shaders/DX11/" + name + ".hlsl";

		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		Compile(vertexInput);
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput)
	{
		mName = name;
		mVertexSource = mPixelSource = filepath;

		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		Compile(vertexInput);
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput)
	{
		mName = name;
		mVertexSource = vertexSrc;
		mPixelSource = pixelSrc;

		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		ReadBinary(vertexInput);
	}

	DX11_Shader::~DX11_Shader()
	{
	}

	void DX11_Shader::Bind() const
	{
		mContext->GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		mContext->GetDeviceContext()->VSSetShader(mVertexShader.Get(), NULL, 0);
		mContext->GetDeviceContext()->PSSetShader(mPixelShader.Get(), NULL, 0);
	}

	void DX11_Shader::Unbind() const
	{
	}

	void DX11_Shader::ReadBinary(const Ref<VertexInput>& vertexInput)
	{
		////////// VERTEX SHADER /////////////////
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
		HRESULT hr = D3DReadFileToBlob(StringToWide(mVertexSource).c_str(), vsBlob.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mVertexSource);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc;

		auto& layout = vertexInput->GetVertexBuffer()->GetLayout();
		for (auto& element : layout)
		{
			layoutDesc.push_back({ element.name.c_str(), 0, DX11BaseType(element.type), 0, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		hr = mContext->GetDevice()->CreateInputLayout(layoutDesc.data(),
			layoutDesc.size(),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			mVertexLayout.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex layout: " + mVertexSource + "\n" + ResultInfo(hr));

		hr = mContext->GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &mVertexShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex shader: " + mVertexSource + "\n" + ResultInfo(hr));

		////////// PIXEL SHADER /////////////////
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
		hr = D3DReadFileToBlob(StringToWide(mPixelSource).c_str(), psBlob.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mPixelSource);

		hr = mContext->GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &mPixelShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create pixel shader: " + mPixelSource + "\n" + ResultInfo(hr));
	}

	void DX11_Shader::Compile(const Ref<VertexInput>& vertexInput)
	{
		////////// VERTEX SHADER /////////////////
		ID3DBlob* vertexErrorMessage;
		HRESULT hr = D3DCompileFromFile(StringToWide(mVertexSource).c_str(), NULL, NULL, "VSMain", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS,
			0, &mVertexShaderBuffer, &vertexErrorMessage);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mVertexSource + "\n" + reinterpret_cast<const char*>(vertexErrorMessage->GetBufferPointer()));

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc;

		auto& layout = vertexInput->GetVertexBuffer()->GetLayout();
		for (auto& element : layout)
		{
			layoutDesc.push_back({ element.name.c_str(), 0, DX11BaseType(element.type), 0, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		hr = mContext->GetDevice()->CreateInputLayout(layoutDesc.data(),
			layoutDesc.size(),
			mVertexShaderBuffer->GetBufferPointer(),
			mVertexShaderBuffer->GetBufferSize(),
			mVertexLayout.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex layout: " + mVertexSource + "\n" + ResultInfo(hr));

		hr = mContext->GetDevice()->CreateVertexShader(mVertexShaderBuffer->GetBufferPointer(), mVertexShaderBuffer->GetBufferSize(), NULL, &mVertexShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex shader: " + mVertexSource + "\n" + ResultInfo(hr));

		////////// PIXEL SHADER /////////////////
		ID3DBlob* pixelErrorMessage;
		hr = D3DCompileFromFile(StringToWide(mPixelSource).c_str(), NULL, NULL, "PSMain", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS,
			0, mPixelShaderBuffer.GetAddressOf(), &pixelErrorMessage);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mPixelSource + "\n" + reinterpret_cast<const char*>(pixelErrorMessage->GetBufferPointer()));

		hr = mContext->GetDevice()->CreatePixelShader(mPixelShaderBuffer->GetBufferPointer(), mPixelShaderBuffer->GetBufferSize(), NULL, &mPixelShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create pixel shader: " + mPixelSource + "\n" + ResultInfo(hr));
	}
}

#endif