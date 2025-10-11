#include "aio_pch.hpp"

#if defined (AIO_WINDOWS)
#include "DX11_Backend.hpp"

#include "Core/Application.hpp"

namespace aio
{
	DX11_Backend::DX11_Backend()
	{
	}

	DX11_Backend::~DX11_Backend()
	{
	}

	void DX11_Backend::Init()
	{
		mContext = static_cast<DX11_Context*>(Application::Get().GetWindow()->GetContext());
	}

	void DX11_Backend::SetViewport(const Vector2& position, const Vector2& size)
	{
		mContext->ResizeBuffer(size);
	}

	void DX11_Backend::Draw(uint32_t vertexCount)
	{
	}

	void DX11_Backend::DrawIndexed(uint32_t indexCount)
	{
	}

	void DX11_Backend::Clear(const Vector4& color)
	{
		mContext->ClearRenderTargetView(color);
		mContext->SetRenderTarget();
	}

}
#endif