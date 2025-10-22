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

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		AIO_ASSERT(!Exists(name), "Shader already exists!");
		mShaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const Ref<VertexInput>& vertexInput)
	{
		auto shader = Shader::Create(name, vertexInput);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput)
	{
		auto shader = Shader::Create(name, filepath, vertexInput);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput)
	{
		auto shader = Shader::Create(name, vertexSrc, pixelSrc, vertexInput);
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		AIO_ASSERT(Exists(name), "Shader not found!");
		return mShaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return mShaders.find(name) != mShaders.end();
	}
}


