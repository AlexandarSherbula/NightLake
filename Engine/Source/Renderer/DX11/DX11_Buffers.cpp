#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)

#include "DX11_Buffers.hpp"

namespace aio
{
	DX11_VertexBuffer::DX11_VertexBuffer(uint32_t size)
	{
	}

	DX11_VertexBuffer::DX11_VertexBuffer(const void* data, uint32_t size)
	{
	}

	DX11_VertexBuffer::~DX11_VertexBuffer()
	{
	}

	void DX11_VertexBuffer::Bind() const
	{
	}

	void DX11_VertexBuffer::Unbind() const
	{
	}

	void DX11_VertexBuffer::SetData(const void* data, uint32_t size)
	{
	}
}
#endif