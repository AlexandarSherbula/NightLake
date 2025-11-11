#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)

#include "DX11_Buffers.hpp"
#include "Core/Application.hpp"

namespace aio
{
	DX11_VertexBuffer::DX11_VertexBuffer(uint32_t size)
	{
		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		HRESULT hr = mContext->GetDevice()->CreateBuffer(&bufferDesc, nullptr, mBuffer.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer: " + ResultInfo(hr) + "\n");


	}

	DX11_VertexBuffer::DX11_VertexBuffer(const void* data, uint32_t size)
	{
		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = data;

		HRESULT hr = mContext->GetDevice()->CreateBuffer(&bufferDesc, &vertexBufferData, mBuffer.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer: " + ResultInfo(hr) + "\n");
	}

	DX11_VertexBuffer::~DX11_VertexBuffer()
	{
	}

	void DX11_VertexBuffer::Bind() const
	{
		UINT stride = mLayout.GetStride();
		UINT offset = 0;

		mContext->GetDeviceContext()->IASetVertexBuffers(0, 1, mBuffer.GetAddressOf(), &stride, &offset);
	}

	void DX11_VertexBuffer::Unbind() const
	{

	}

	void DX11_VertexBuffer::SetData(const void* data, uint32_t size)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		mContext->GetDeviceContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, data, size);
		mContext->GetDeviceContext()->Unmap(mBuffer.Get(), 0);
	}

	/////////////////////////////////////////////////////
	///////////INDEX BUFFER//////////////////////////////
	/////////////////////////////////////////////////////

	DX11_IndexBuffer::DX11_IndexBuffer(uint32_t* indices, uint32_t count)
	{
		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = count * sizeof(uint32_t);
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));
		indexBufferData.pSysMem = indices;

		HRESULT hr = mContext->GetDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, mBuffer.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create index buffer: " + ResultInfo(hr) + "\n");
	}

	DX11_IndexBuffer::~DX11_IndexBuffer()
	{
		
	}

	void DX11_IndexBuffer::Bind()
	{
		mContext->GetDeviceContext()->IASetIndexBuffer(mBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11_IndexBuffer::Unbind()
	{

	}

	/////////////////////////////////////////////////////
	///////////CONSTANT BUFFER///////////////////////////
	/////////////////////////////////////////////////////

	DX11_ConstantBuffer::DX11_ConstantBuffer(uint32_t block_size, uint32_t slot)
	{
		mContext = std::dynamic_pointer_cast<DX11_Context>(Application::Get().GetAppWindow()->GetContext());

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = static_cast<UINT>(block_size + (16 - (block_size % 16)));
		bufferDesc.StructureByteStride = 0;

		HRESULT hr = mContext->GetDevice()->CreateBuffer(&bufferDesc, 0, mBuffer.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create constant buffer: " + ResultInfo(hr) + "\n");
	}

	DX11_ConstantBuffer::~DX11_ConstantBuffer()
	{
	}

	void DX11_ConstantBuffer::SetData(const void* data, uint32_t size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = mContext->GetDeviceContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to map constant buffer: " + ResultInfo(hr) + "\n");
		memcpy(mappedResource.pData, data, size);
		mContext->GetDeviceContext()->Unmap(mBuffer.Get(), 0);
	}

	void DX11_ConstantBuffer::Bind(uint32_t binding)
	{
		mContext->GetDeviceContext()->VSSetConstantBuffers(binding, 1, mBuffer.GetAddressOf());
	}

	DX11_VertexInput::DX11_VertexInput()
	{
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
	}

	DX11_VertexInput::~DX11_VertexInput()
	{
	}

	void DX11_VertexInput::Bind() const
	{
		mVertexBuffer->Bind();

		if (mIndexBuffer != nullptr)
			mIndexBuffer->Bind();
	}

	void DX11_VertexInput::Unbind() const
	{
	}

	void DX11_VertexInput::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		mVertexBuffer = vertexBuffer;
	}

	void DX11_VertexInput::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		mIndexBuffer = indexBuffer;
	}
}
#endif