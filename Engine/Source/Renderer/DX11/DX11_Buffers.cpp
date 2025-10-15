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

	/////////////////////////////////////////////////////
	///////////INDEX BUFFER//////////////////////////////
	/////////////////////////////////////////////////////

	DX11_IndexBuffer::DX11_IndexBuffer(uint32_t* indices, uint32_t count)
	{
	}

	DX11_IndexBuffer::~DX11_IndexBuffer()
	{
	}

	void DX11_IndexBuffer::Bind()
	{
	}

	void DX11_IndexBuffer::Unbind()
	{
	}

	/////////////////////////////////////////////////////
	///////////CONSTANT BUFFER///////////////////////////
	/////////////////////////////////////////////////////

	DX11_ConstantBuffer::DX11_ConstantBuffer(uint32_t block_size, uint32_t slot)
	{
	}

	DX11_ConstantBuffer::~DX11_ConstantBuffer()
	{
	}

	void DX11_ConstantBuffer::SetData(const void* data, uint32_t data_size)
	{
	}

	void DX11_ConstantBuffer::Bind(uint32_t binding)
	{
	}

	DX11_VertexInput::DX11_VertexInput()
	{
	}

	DX11_VertexInput::~DX11_VertexInput()
	{
	}

	void DX11_VertexInput::Bind() const
	{
	}

	void DX11_VertexInput::Unbind() const
	{
	}

	void DX11_VertexInput::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
	}

	void DX11_VertexInput::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
	}
}
#endif