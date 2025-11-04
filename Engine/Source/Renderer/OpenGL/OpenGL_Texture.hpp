#pragma once

#include "Renderer/Texture.hpp"
#include <cstdint>

namespace aio
{
	class OpenGL_Texture : public Texture
	{
	public:
		OpenGL_Texture(const TextureSpecification& specification, const std::filesystem::path& filepath, std::string name = "");

		~OpenGL_Texture();

		void Bind(uint32_t slot) const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;
	private:
		GLenum mUploadImageFormat;
	};
}


