#pragma once

#include "Renderer/Texture.hpp"

namespace aio
{
	class OpenGL_Texture : public Texture
	{
	public:
		OpenGL_Texture(uint32_t width, uint32_t height);
		OpenGL_Texture(const std::string& filepath, std::string name = "");

		~OpenGL_Texture();

		void Bind(uint32_t slot) const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;
	private:
		GLenum mInternalFormat, mDataFormat;
	};
}


