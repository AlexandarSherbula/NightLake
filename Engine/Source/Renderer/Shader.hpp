#pragma once

#include <string>

#include "Utils/Utilities.hpp"
#include "Utils/Math.hpp"
#include "Buffers.hpp"

#include "Utils/FileReading.hpp"

#include "slang.h"
#include "slang-com-helper.h"
#include "slang-com-ptr.h"


namespace aio
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Ref<Shader> Create(const std::string& filepath, const Ref<VertexInput>& vertexInput, std::string name = "");
		static Ref<Shader> Create(const std::string& name, const std::string& vertexFile, const std::string& pixelFile, const Ref<VertexInput>& vertexInput);
		static Ref<Shader> CreateAsset(const std::string& shaderFile, const Ref<VertexInput>& vertexInput, std::string name = "");

		static Ref<Shader> Get(const std::string& name);
		static void Add(const Ref<Shader>& shader, const std::string& name = "");
		static bool Exists(const std::string& name);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		inline const std::string& GetName() const { return mName; }
	protected:
		std::string mName;
	private:
		static std::unordered_map<std::string, Ref<Shader>> sShaders;
	};

	class SlangCompiler
	{
	public:
		static void Run(const std::string& slangFile, const std::string& name);
		static void Reflection();

		inline static std::string GetShaderCacheDirectory() {	return CACHE_DIRECTORY + "shaders/"; }
		static std::string GetVertexShaderCacheFilePath(const std::string& shaderName);
		static std::string GetPixelShaderCacheFilePath(const std::string& shaderName);
	private:
		static void DiagnoseIfNeeded(slang::IBlob* diagnosticsBlob);
	private:
		static Slang::ComPtr<slang::IGlobalSession> sGlobalSession;

		static std::unordered_map<std::string, size_t> sShaderHashes;
		static std::string sSlangShaderFilePath;
		static std::string sSlangShaderFileSource;
	};

	
}