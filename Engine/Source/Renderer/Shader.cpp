#include "aio_pch.hpp"
#include "Shader.hpp"

#include "Renderer.hpp"

#include "OpenGL/OpenGL_Shader.hpp"
#include "DX11/DX11_Shader.hpp"

#include "Utils/Timer.hpp"

#include "Core/Assets.hpp"

namespace aio
{
	static std::string GetSampledTexture();
	Slang::ComPtr<slang::IGlobalSession> SlangCompiler::sGlobalSession;

	std::unordered_map<std::string, Ref<Shader>> Shader::sShaders;

	void SlangCompiler::Run(const std::string& slangFile, const std::string& name)
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

		std::string shaderSource = ReadFromFiles(slangFile);

		if (shaderSource.find("GetSampledTexture") != std::string::npos)
		{
			std::string SampleTextureFunctionDefintion = GetSampledTexture();

			if (Renderer::GetAPI() == OpenGL && shaderSource.find("Texture2D") != std::string::npos)
			{
				std::string typedefAdd = "typedef Sampler2D Texture2D;\n";
				shaderSource = typedefAdd + shaderSource + "\n" + SampleTextureFunctionDefintion;
			}
			else
				shaderSource += "\n" + SampleTextureFunctionDefintion;
		}

		Slang::ComPtr<slang::IModule> slangModule;
		{
			Slang::ComPtr<slang::IBlob> diagnosticsBlob;
			slangModule = session->loadModuleFromSourceString(
				name.c_str(),
				slangFile.c_str(),
				shaderSource.c_str(),
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
				std::filesystem::create_directories(GetShaderCacheDirectory());

				std::ofstream file(filepath, std::ios::binary);
				if (!file)
					return false;

				file.write(
					reinterpret_cast<const char*>(blob->getBufferPointer()),
					static_cast<std::streamsize>(blob->getBufferSize())
				);

				return file.good();
			};

		writeBlobToFile(GetVertexShaderCacheFilePath(name), vsCode);
		writeBlobToFile(GetPixelShaderCacheFilePath(name), psCode);

		/////////////////////////////////////////////////////
		//////////////REFLECTION/////////////////////////////
		/////////////////////////////////////////////////////


		auto PrintKind = [](slang::TypeReflection::Kind kind)
			{
				typedef slang::TypeReflection::Kind Kind;

				switch (kind)
				{
				case Kind::None:                        return "None";
				case Kind::Struct:                      return "Struct";
				case Kind::Array:                       return "Array";
				case Kind::Matrix:                      return "Matrix";
				case Kind::Vector:                      return "Vector";
				case Kind::Scalar:                      return "Scalar";
				case Kind::ConstantBuffer:              return "ConstantBuffer";
				case Kind::Resource:                    return "Resource";
				case Kind::SamplerState:                return "SamplerState";
				case Kind::TextureBuffer:               return "TextureBuffer";
				case Kind::ShaderStorageBuffer:         return "ShaderStorageBuffer";
				case Kind::ParameterBlock:              return "ParameterBlock";
				case Kind::GenericTypeParameter:        return "GenericTypeParameter";
				case Kind::Interface:                   return "Interface";
				case Kind::OutputStream:                return "OutputStream";
				case Kind::Specialized:                 return "Specialized";
				case Kind::Feedback:                    return "Feedback";
				case Kind::Pointer:                     return "Pointer";
				case Kind::DynamicResource:             return "DynamicResource";
				case Kind::MeshOutput:                  return "MeshOutput";
				}

				return "";
			};

		printf("\n");
		AIO_LOG_TRACE("SLANG COMPILING REFLECTION");
		slang::ProgramLayout* layout = linkedProgram->getLayout(0);
		int paramCount = layout->getParameterCount();

		for (int i = 0; i < paramCount; ++i)
		{
			auto param = layout->getParameterByIndex(i);
			const char* name = param->getName();
			AIO_LOG_TRACE("parameter name: {0}", name);
			auto typeLayout = param->getTypeLayout();
			AIO_LOG_TRACE("  kind: {0}", PrintKind(typeLayout->getKind()));

			int catCount = param->getCategoryCount();
			for (int ci = 0; ci < catCount; ++ci)
			{
				auto cat = param->getCategoryByIndex(ci);
				size_t slot = param->getOffset(cat);
				AIO_LOG_TRACE("  binding slot: {0}", slot);
			}

			switch (typeLayout->getKind())
			{
			case slang::TypeReflection::Kind::Array:
				AIO_LOG_TRACE("  array element size: {0}", typeLayout->getElementCount());
				if (auto elemLayout = typeLayout->getElementTypeLayout())
				{
					AIO_LOG_TRACE("    element kind: {0}", PrintKind(elemLayout->getKind()));
				}
				break;
			case slang::TypeReflection::Kind::ConstantBuffer:
			case slang::TypeReflection::Kind::ParameterBlock:
			case slang::TypeReflection::Kind::TextureBuffer:
			case slang::TypeReflection::Kind::ShaderStorageBuffer:
			{
				auto elementVarLayout = typeLayout->getElementVarLayout();
				if (elementVarLayout)
				{
					auto elemTypeLayout = elementVarLayout->getTypeLayout();
					size_t size = elemTypeLayout->getSize();
					AIO_LOG_TRACE("  field kind: {0}", PrintKind(elemTypeLayout->getKind()));
					AIO_LOG_TRACE("  size={0}", size);
				}
				break;
			}
			}
		}
	}

	std::string SlangCompiler::GetVertexShaderCacheFilePath(const std::string& shaderName)
	{
		std::string fileExtension;

		CHECK_API
		(
			fileExtension = ".vert",
			fileExtension = ".cso"
		);

		return SlangCompiler::GetShaderCacheDirectory() + shaderName + "-vs" + fileExtension;
	}

	std::string SlangCompiler::GetPixelShaderCacheFilePath(const std::string& shaderName)
	{
		std::string fileExtension;

		CHECK_API
		(
			fileExtension = ".frag",
			fileExtension = ".cso"
		);

		return SlangCompiler::GetShaderCacheDirectory() + shaderName + "-ps" + fileExtension;
	}

	void SlangCompiler::DiagnoseIfNeeded(slang::IBlob* diagnosticsBlob)
	{
		if (diagnosticsBlob != nullptr)
		{
			AIO_LOG_ERROR((const char*)diagnosticsBlob->getBufferPointer());
		}
	}

	Ref<Shader> Shader::Create(const std::string& filepath, const Ref<VertexInput>& vertexInput, std::string name)
	{
		if (name == "")
			name = GetFileName(filepath);

		if (filepath.find(".slang") != std::string::npos)
		{
			std::filesystem::path vsPath = SlangCompiler::GetVertexShaderCacheFilePath(name);
			std::filesystem::path psPath = SlangCompiler::GetPixelShaderCacheFilePath(name);

			//if (!std::filesystem::exists(vsPath) || !std::filesystem::exists(psPath))
			//{
				SlangCompiler::Run(filepath, name);
			//}

			return Shader::Create(name, vsPath.string(), psPath.string(), vertexInput);
		}

		CHECK_API
		(
			return CreateRef<OpenGL_Shader>(name, filepath, vertexInput),
			return CreateRef<DX11_Shader>(name, filepath, vertexInput)
		);
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexFile, const std::string& pixelFile, const Ref<VertexInput>& vertexInput)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_Shader>(name, vertexFile, pixelFile, vertexInput),
			return CreateRef<DX11_Shader>(name, vertexFile, pixelFile, vertexInput)
		);
		return nullptr;
	}

	Ref<Shader> Shader::CreateAsset(const std::string& shaderFile, const Ref<VertexInput>& vertexInput, std::string name)
	{
		if (name == "")
			name = GetFileName(shaderFile);

		std::string shaderFilePath = ASSETS_DIRECTORY "shaders/" + shaderFile;

		auto shader = Create(shaderFilePath, vertexInput, name);
		Shader::Add(shader, name);
		return shader;
	}

	Ref<Shader> Shader::Get(const std::string& name)
	{
		AIO_ASSERT(Exists(name), "Shader doesn't exist!");
		return sShaders[name];
	}

	void Shader::Add(const Ref<Shader>& shader, const std::string& name)
	{
		AIO_ASSERT(!Exists(name), "Shader already exists!");
		sShaders[name] = shader;
	}

	bool Shader::Exists(const std::string& name)
	{
		return sShaders.find(name) != sShaders.end();
	}


	std::string GetSampledTexture()
	{
		CHECK_API
		(
			return R"(
				float4 GetSampledTexture(float2 texCoord, int texIndex)
				{
				return textures[texIndex].Sample(texCoord);
				})",

			return R"(
				float4 GetSampledTexture(float2 texCoord, int texIndex)
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


