#include "aio_pch.hpp"
#include "Texture.hpp"

#if defined (AIO_LINUX)
	#define STBI_NO_SIMD
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include "Renderer/Renderer.hpp"
#include "OpenGL/OpenGL_Texture.hpp"
#include "DX11/DX11_Texture.hpp"

namespace aio
{
	std::unordered_map<std::string, Ref<Texture>> Texture::sTextures;

	Ref<Texture> Texture::Create(uint32_t width, uint32_t height)
	{
		CHECK_API(
			return CreateRef<OpenGL_Texture>(width, height),
			return CreateRef<DX11_Texture>(width, height)
		);

		return nullptr;
	}

	Ref<Texture> Texture::Create(const std::string& filepath, std::string name)
	{
		if (name == "")
			name = GetFileName(filepath);

		CHECK_API(
			return CreateRef<OpenGL_Texture>(filepath),
			return CreateRef<DX11_Texture>(filepath)
		);

		return nullptr;
	}

	Ref<Texture> Texture::CreateAsset(const std::string& imageFile, std::string name)
	{
		if (name == "")
			name = GetFileName(imageFile);

		std::string textureFilePath = ASSETS_DIRECTORY + "images/" + imageFile;
		auto texture = Texture::Create(textureFilePath, name);
		Add(texture, name);
		return texture;
	}

	Ref<Texture> Texture::Get(const std::string& name)
	{
		AIO_ASSERT(Exists(name), "Texture not found!");
		return sTextures[name];
	}

	void Texture::Add(const Ref<Texture>& texture, std::string name)
	{
		AIO_ASSERT(!Exists(name), "Texture already exists!");
		sTextures[name] = texture;
	}

	bool Texture::Exists(const std::string& name)
	{
		return sTextures.find(name) != sTextures.end();
	}
}


