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

	Ref<ConstantBuffer> ConstantBuffer::Create(uint32_t block_size, uint32_t slot)
	{
		CHECK_API
		(
			return CreateRef<UniformBuffer>(block_size, slot),
			return CreateRef<DX11_ConstantBuffer>(block_size, slot)
		);

		return nullptr;
	}

	Ref<VertexInput> VertexInput::Create()
	{
		CHECK_API
		(
			return CreateRef<VertexArray>(),
			return CreateRef<DX11_VertexInput>()
		);

		return nullptr;
	}
	
}


