#pragma once

#include "Renderer/Shader.hpp"

#if defined (AIO_WINDOWS)
#include <d3d11.h>
#include <wrl/client.h>

#include "DX11_Context.hpp"

namespace aio
{
	class DX11_Shader : public Shader
	{
	public:
		DX11_Shader(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput);
		DX11_Shader(const std::string& name, const std::string& vertexFile, const std::string& pixelFile, const Ref<VertexInput>& vertexInput);
		~DX11_Shader();

		void Bind() const override;
		void Unbind() const override;

	private:
		void Compile(const Ref<VertexInput>& vertexInput);
		void ReadBinary(const Ref<VertexInput>& vertexInput);
	private:
		std::string mVertexFile;
		std::string mPixelFile;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> mVertexShaderBuffer;

		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> mPixelShaderBuffer;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> mVertexLayout;

		Ref<DX11_Context> mContext;
	};
}
#else
namespace aio
{
	class DX11_Shader : public Shader
	{
	public:
		DX11_Shader(const std::string& name, const Ref<VertexInput>& vertexInput) {}
		DX11_Shader(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput) {}
		DX11_Shader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput) {}
		~DX11_Shader() {}
	
	
		void Bind() const override {}
		void Unbind() const override {}
	private:
		void Compile(const Ref<VertexInput>& vertexInput) {}
	};
}
#endif