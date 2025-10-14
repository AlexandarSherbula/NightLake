#pragma once

#include "Renderer/Buffers.hpp"

#if defined(AIO_WINDOWS)
#include <d3d11.h>
#include <wrl/client.h>

namespace aio
{
	class DX11_VertexBuffer : public VertexBuffer
	{
	public:
		DX11_VertexBuffer(uint32_t size);
		DX11_VertexBuffer(const void* data, uint32_t size);

		~DX11_VertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	};

	class DX11_IndexBuffer : public IndexBuffer
	{
	public:
		DX11_IndexBuffer(uint32_t* indices, uint32_t count);
		~DX11_IndexBuffer();

		void Bind() override;
		void Unbind() override;

	private:
		uint32_t mID;
	};

	class DX11_ConstantBuffer : public ConstantBuffer
	{
	public:
		DX11_ConstantBuffer(uint32_t block_size, uint32_t slot);
		~DX11_ConstantBuffer();

		void SetData(const void* data, uint32_t data_size) override;
		void Bind(uint32_t binding) override;
	private:
		uint32_t mID;
	};
}
#else
namespace aio
{
	class DX11_VertexBuffer : public VertexBuffer
	{
	public:
		DX11_VertexBuffer(uint32_t size) {}
		DX11_VertexBuffer(const void* data, uint32_t size) {}

		~DX11_VertexBuffer() {}

		void Bind() const override {}
		void Unbind() const override {}

		void SetData(const void* data, uint32_t size) override {}
	};

	class DX11_IndexBuffer : public IndexBuffer
	{
	public:
		DX11_IndexBuffer(uint32_t* indices, uint32_t count) {}
		~DX11_IndexBuffer() {}

		void Bind() override {}
		void Unbind() override {}
	};

	class DX11_ConstantBuffer : public ConstantBuffer
	{
	public:
		DX11_ConstantBuffer(uint32_t block_size, uint32_t slot) {}
		~DX11_ConstantBuffer() {}

		void SetData(const void* data, uint32_t data_size) override {}
		void Bind(uint32_t binding) override {}
	};
}
#endif