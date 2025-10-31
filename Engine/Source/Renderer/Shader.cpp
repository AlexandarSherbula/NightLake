#include "aio_pch.hpp"
#include "Shader.hpp"

#include "Renderer.hpp"

#include "OpenGL/OpenGL_Shader.hpp"
#include "DX11/DX11_Shader.hpp"

#include "Utils/FileReading.hpp"

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

	Ref<Shader> ShaderLibrary::LoadSlang(const std::string& name, const Ref<VertexInput>& vertexInput)
	{
		std::filesystem::path vsPath = SlangShader::GetVertexShaderCacheFilePath(name);
		std::filesystem::path psPath = SlangShader::GetPixelShaderCacheFilePath(name);

		if (!std::filesystem::exists(vsPath) || !std::filesystem::exists(psPath))
		{
			SlangShader::Compile(name);
		}

		auto shader = Shader::Create(name, vsPath.string(), psPath.string(), vertexInput);
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

	Slang::ComPtr<slang::IGlobalSession> SlangShader::sGlobalSession;
	std::string SlangShader::sCacheDirectory = GetProjectDirectory() + "Sandbox/Assets/shaders/Cache";

	static std::string SampleTexture();


	void SlangShader::Compile(const std::string& shaderName)
	{
		createGlobalSession(sGlobalSession.writeRef());

		slang::SessionDesc sessionDesc = {};
		slang::TargetDesc targetDesc = {};

		auto profileName = []()
			{
				CHECK_API(return "glsl_450", return "sm_5_0");
				return "";
			};

		auto targetFormat = []()
			{
				CHECK_API(return SLANG_GLSL, return SLANG_DXBC);
				return SLANG_TARGET_UNKNOWN;
			};

		targetDesc.format = targetFormat();
		targetDesc.profile = sGlobalSession->findProfile(profileName());

		sessionDesc.targets = &targetDesc;
		sessionDesc.targetCount = 1;

		Slang::ComPtr<slang::ISession> session;
		sGlobalSession->createSession(sessionDesc, session.writeRef());

		std::string proj = GetProjectDirectory();

		std::string slangShaderFilePath = GetProjectDirectory() + "Sandbox/Assets/shaders/" + shaderName + ".slang";

		std::string slangShaderFileSource = ReadFromFiles(slangShaderFilePath);

		std::string SampleTextureFunctionDeclaration = "float4 SampleTexture(float2 texCoord, int texIndex = 0);";
		if (slangShaderFileSource.find(SampleTextureFunctionDeclaration) != std::string::npos)
		{
			std::string SampleTextureFunctionDefintion = SampleTexture();

			if (Renderer::GetAPI() == OpenGL)
			{
				std::string typedefAdd = "typedef Sampler2D Texture2D;\n";
				slangShaderFileSource = typedefAdd + slangShaderFileSource + "\n" + SampleTextureFunctionDefintion;
			}
			else
				slangShaderFileSource = slangShaderFileSource + "\n" + SampleTextureFunctionDefintion;
		}
		
		Slang::ComPtr<slang::IModule> slangModule;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			slangModule = session->loadModuleFromSourceString(
				shaderName.c_str(),
				slangShaderFilePath.c_str(),
				slangShaderFileSource.c_str(),
				diagnosticsBlob.writeRef());
			DiagnoseIfNeeded(diagnosticsBlob);
			AIO_ASSERT(slangModule, "Failed to create a slang module");
		}

		Slang::ComPtr<slang::IEntryPoint> vsEntry, psEntry;
		slangModule->findEntryPointByName("VSMain", vsEntry.writeRef());
		AIO_ASSERT(vsEntry, "Failed to get Vertex Shader entry point");

		slangModule->findEntryPointByName("PSMain", psEntry.writeRef());
		AIO_ASSERT(psEntry, "Failed to get Pixel Shader entry point");

		std::array<slang::IComponentType*, 3> componentTypes = { slangModule, vsEntry, psEntry };
		Slang::ComPtr<slang::IComponentType> slangProgram;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			SlangResult result = session->createCompositeComponentType(
				componentTypes.data(),
				componentTypes.size(),
				slangProgram.writeRef(),
				diagnosticsBlob.writeRef());
			DiagnoseIfNeeded(diagnosticsBlob);
			AIO_ASSERT(SLANG_SUCCEEDED(result), "Failed to create a program");
		}

		Slang::ComPtr<slang::IComponentType> linkedProgram;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			SlangResult result = slangProgram->link(
				linkedProgram.writeRef(),
				diagnosticsBlob.writeRef());
			DiagnoseIfNeeded(diagnosticsBlob);
			AIO_ASSERT(SLANG_SUCCEEDED(result), "Failed to link a program");
		}

		Slang::ComPtr<slang::IBlob> vsCode;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			linkedProgram->getEntryPointCode(0, 0, vsCode.writeRef(), diagnosticsBlob.writeRef());
			SlangResult result = linkedProgram->getEntryPointCode(
				0, // entry point index
				0, // target index
				vsCode.writeRef(),
				diagnosticsBlob.writeRef());
			DiagnoseIfNeeded(diagnosticsBlob);
			AIO_ASSERT(SLANG_SUCCEEDED(result), "Failed to create Vertex Shader code blob");
		}

		Slang::ComPtr<slang::IBlob> psCode;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			linkedProgram->getEntryPointCode(1, 0, psCode.writeRef(), diagnosticsBlob.writeRef());
			SlangResult result = linkedProgram->getEntryPointCode(
				1, // entry point index
				0, // target index
				psCode.writeRef(),
				diagnosticsBlob.writeRef());
			DiagnoseIfNeeded(diagnosticsBlob);
			AIO_ASSERT(SLANG_SUCCEEDED(result), "Failed to create Pixel Shader code blob");
		}

		AIO_LOG_INFO("Vertex Shader succesfully compiled to {0} bytes of binary", vsCode->getBufferSize());
		AIO_LOG_INFO("Pixel Shader succesfully compiled to {0} bytes of binary", psCode->getBufferSize());

		auto writeBlobToFile = [](const std::string& filepath, slang::IBlob* blob)
			{
				std::filesystem::create_directories(sCacheDirectory);

				std::ofstream file(filepath, std::ios::binary);
				if (!file)
					return false;

				file.write(
					reinterpret_cast<const char*>(blob->getBufferPointer()),
					static_cast<std::streamsize>(blob->getBufferSize())
				);

				return file.good();
			};

		writeBlobToFile(GetVertexShaderCacheFilePath(shaderName), vsCode);
		writeBlobToFile(GetPixelShaderCacheFilePath(shaderName), psCode);
	}

	void SlangShader::CompileFromFilePath(const std::string& filePath)
	{
	}

	void SlangShader::Reflection()
	{
	}

	std::string SlangShader::GetVertexShaderCacheFilePath(const std::string& shaderName)
	{
		std::string fileExtension;

		CHECK_API
		(
			fileExtension = ".vert",
			fileExtension = ".cso"
		);

		return SlangShader::GetCacheDirectory() + "/" + shaderName + "-vs" + fileExtension;
	}

	std::string SlangShader::GetPixelShaderCacheFilePath(const std::string& shaderName)
	{
		std::string fileExtension;

		CHECK_API
		(
			fileExtension = ".frag",
			fileExtension = ".cso"
		);

		return SlangShader::GetCacheDirectory() + "/" + shaderName + "-ps" + fileExtension;
	}

	void SlangShader::DiagnoseIfNeeded(slang::IBlob* diagnosticsBlob)
	{
		if (diagnosticsBlob != nullptr)
		{
			AIO_LOG_ERROR((const char*)diagnosticsBlob->getBufferPointer());
		}
	}

	std::string SampleTexture()
	{
		CHECK_API
		(
			return R"(
				float4 SampleTexture(float2 texCoord, int texIndex)
				{
				return textures[texIndex].Sample(texCoord);
				})",

			return R"(
				float4 SampleTexture(float2 texCoord, int texIndex)
				{
				switch (texIndex)
				{
				case 0: return textures[0].Sample(samplerState, texCoord);
				case 1: return textures[1].Sample(samplerState, texCoord);
				case 2: return textures[2].Sample(samplerState, texCoord);
				case 3: return textures[3].Sample(samplerState, texCoord);
				case 4: return textures[4].Sample(samplerState, texCoord);
				case 5: return textures[5].Sample(samplerState, texCoord);
				case 6: return textures[6].Sample(samplerState, texCoord);
				case 7: return textures[7].Sample(samplerState, texCoord);
				case 8: return textures[8].Sample(samplerState, texCoord);
				case 9: return textures[9].Sample(samplerState, texCoord);
				case 10: return textures[10].Sample(samplerState, texCoord);
				case 11: return textures[11].Sample(samplerState, texCoord);
				case 12: return textures[12].Sample(samplerState, texCoord);
				case 13: return textures[13].Sample(samplerState, texCoord);
				case 14: return textures[14].Sample(samplerState, texCoord);
				case 15: return textures[15].Sample(samplerState, texCoord);
				case 16: return textures[16].Sample(samplerState, texCoord);
				case 17: return textures[17].Sample(samplerState, texCoord);
				case 18: return textures[18].Sample(samplerState, texCoord);
				case 19: return textures[19].Sample(samplerState, texCoord);
				case 20: return textures[20].Sample(samplerState, texCoord);
				case 21: return textures[21].Sample(samplerState, texCoord);
				case 22: return textures[22].Sample(samplerState, texCoord);
				case 23: return textures[23].Sample(samplerState, texCoord);
				case 24: return textures[24].Sample(samplerState, texCoord);
				case 25: return textures[25].Sample(samplerState, texCoord);
				case 26: return textures[26].Sample(samplerState, texCoord);
				case 27: return textures[27].Sample(samplerState, texCoord);
				case 28: return textures[28].Sample(samplerState, texCoord);
				case 29: return textures[29].Sample(samplerState, texCoord);
				case 30: return textures[30].Sample(samplerState, texCoord);
				case 31: return textures[31].Sample(samplerState, texCoord);
				}
				return float4(1.0, 1.0, 1.0, 1.0);
				})"
		);

		return "";
	}
}


