#pragma once

#include <string>

#include "Utils/Utilities.hpp"
#include "Utils/Math.hpp"
#include "Buffers.hpp"

#include "slang.h"
#include "slang-com-helper.h"
#include "slang-com-ptr.h"

namespace aio
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Ref<Shader> Create(const std::string& name, const Ref<VertexInput>& vertexInput);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int32_t value) = 0;
		virtual void SetIntArray(const std::string& name, int32_t* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, float value) {}
		virtual void SetFloat2(const std::string& name, const Vector2& value) {}
		virtual void SetFloat3(const std::string& name, const Vector3& value) {}
		virtual void SetFloat4(const std::string& name, const Vector4& value) {}

		virtual void SetMat3x3(const std::string& name, const glm::mat3x3& matrix) {}
		virtual void SetMat4x4(const std::string& name, const Mat4x4& matrix) {}

		inline const std::string& GetName() const { return mName; }
	protected:
		std::string mName;
	};

	class SlangShader
	{
	public:
		static void Compile(const std::string& shaderName);
		static void CompileFromFilePath(const std::string& filePath);
		static void Reflection();

		inline static std::string GetCacheDirectory() {	return sCacheDirectory; }
		static std::string GetVertexShaderCacheFilePath(const std::string& shaderName);
		static std::string GetPixelShaderCacheFilePath(const std::string& shaderName);
	private:
		static void DiagnoseIfNeeded(slang::IBlob* diagnosticsBlob);
	private:
		static Slang::ComPtr<slang::IGlobalSession> sGlobalSession;

		static std::string sCacheDirectory;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const Ref<VertexInput>& vertexInput);
		Ref<Shader> Load(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput);
		Ref<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexInput>& vertexInput);
		Ref<Shader> LoadSlang(const std::string& name, const Ref<VertexInput>& vertexInput);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> mShaders;
	};

	
}