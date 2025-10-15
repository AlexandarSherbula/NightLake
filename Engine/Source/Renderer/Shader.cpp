#include "aio_pch.hpp"
#include "Shader.hpp"

#include "Renderer.hpp"

#include "OpenGL/OpenGL_Shader.hpp"
#include "DX11/DX11_Shader.hpp"

namespace aio
{
	Ref<Shader> Shader::Create(const std::string& name, const Ref<VertexInput>& vertexInput)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_Shader>(name, vertexInput),
			return CreateRef<DX11_Shader>(name, vertexInput)
		);
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_Shader>(name, filepath, vertexInput),
			return CreateRef<DX11_Shader>(name, filepath, vertexInput)
		);
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_Shader>(name, vertexSrc, pixelSrc, vertexInput),
			return CreateRef<DX11_Shader>(name, vertexSrc, pixelSrc, vertexInput)
		);
		return nullptr;
	}
}


