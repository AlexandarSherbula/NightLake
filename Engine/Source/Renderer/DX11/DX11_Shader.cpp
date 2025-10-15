#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)

#include "DX11_Shader.hpp"

namespace aio
{
	DX11_Shader::DX11_Shader(const std::string& name, const Ref<VertexInput>& vertexInput)
	{
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput)
	{
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput)
	{
	}

	DX11_Shader::~DX11_Shader()
	{
	}

	void DX11_Shader::Bind() const
	{
	}

	void DX11_Shader::Unbind() const
	{
	}

	void DX11_Shader::SetInt(const std::string& name, int32_t value)
	{
	}

	void DX11_Shader::SetIntArray(const std::string& name, int32_t* values, uint32_t count)
	{
	}

	void DX11_Shader::SetFloat(const std::string& name, float value)
	{
	}

	void DX11_Shader::SetFloat2(const std::string& name, const Vector2& value)
	{
	}

	void DX11_Shader::SetFloat3(const std::string& name, const Vector3& value)
	{
	}

	void DX11_Shader::SetFloat4(const std::string& name, const Vector4& value)
	{
	}

	void DX11_Shader::SetMat3x3(const std::string& name, const glm::mat3x3& matrix)
	{
	}

	void DX11_Shader::SetMat4x4(const std::string& name, const Mat4x4& matrix)
	{
	}

	void DX11_Shader::Compile(const Ref<VertexInput>& vertexInput)
	{
	}
}

#endif