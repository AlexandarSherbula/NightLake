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

		AIO_ASSERT(false, "API has not been selected.\n");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
	{
		CHECK_API
		(
			return CreateRef<OpenGL_VertexBuffer>(data, size),
			return CreateRef<DX11_VertexBuffer>(data, size)
		);

		AIO_ASSERT(false, "API has not been selected.\n");
		return nullptr;
	}
}


