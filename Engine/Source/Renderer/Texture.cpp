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
	Ref<Texture> Texture::Create(uint32_t width, uint32_t height, uint32_t whiteTexture)
	{
		CHECK_API(
			return CreateRef<OpenGL_Texture>(width, height, whiteTexture),
			return CreateRef<DX11_Texture>(width, height, whiteTexture)
		);

		return nullptr;
	}

	Ref<Texture> Texture::Create(const std::string& filepath)
	{
		CHECK_API(
			return CreateRef<OpenGL_Texture>(filepath),
			return CreateRef<DX11_Texture>(filepath)
		);

		return nullptr;
	}
}


