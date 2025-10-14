#pragma once

#include "Renderer/Buffers.hpp"

namespace aio
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(uint32_t size);
		OpenGL_VertexBuffer(const void* data, uint32_t size);

		~OpenGL_VertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t mVBO;
		uint32_t mVAO;
	};
}