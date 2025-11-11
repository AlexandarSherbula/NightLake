#pragma once

#include "Utils/Utilities.hpp"
#include "Utils/Math.hpp"

#include "Window/Window.hpp"

namespace aio
{
	enum class DrawingMode
	{
		None = 0,
		Point,
		Lines,
		Triangles
	};


	class RendererBackend
	{
	public:
		virtual ~RendererBackend() = default;

		static Scope<RendererBackend> Create();

		virtual void Init() = 0;
		virtual void SetViewport(const Vector2& position, const Vector2& size) = 0;
		virtual void Draw(DrawingMode mode, uint32_t vertexCount) = 0;
		virtual void DrawIndexed(DrawingMode mode, uint32_t indexCount) = 0;
		virtual void Clear(const Vector4& color) = 0;

		virtual std::string GetName() const = 0;	
	};
}