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
}
#else
//namespace aio
//{
//	class DX11_VertexBuffer : public VertexBuffer
//	{
//	public:
//		DX11_VertexBuffer(uint32_t size) {}
//		DX11_VertexBuffer(const void* data, uint32_t size) {}
//
//		~DX11_VertexBuffer() {}
//
//		void Bind() const override {}
//		void Unbind() const override {}
//
//		void SetData(const void* data, uint32_t size) override {}
//	};
//}
#endif