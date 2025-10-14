#include "aio_pch.hpp"
#include "Buffers.hpp"

#include "Renderer.hpp"
#include "OpenGL/OpenGL_Buffers.hpp"
#include "DX11/DX11_Buffers.hpp"

namespace aio
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_VertexBuffer>(size),
			return CreateRef<DX11_VertexBuffer>(size)
		);

		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_VertexBuffer>(data, size),
			return CreateRef<DX11_VertexBuffer>(data, size)
		);

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_IndexBuffer>(indices, count),
			return CreateRef<DX11_IndexBuffer>(indices, count)
		);

		return nullptr;
	}
}


