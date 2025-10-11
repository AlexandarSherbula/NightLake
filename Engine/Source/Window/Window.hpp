#pragma once

#include "Utils/Utilities.hpp"
#include "Events/Events.hpp"
#include "Input/Input.hpp"
#include "Renderer/GraphicsContext.hpp"

#include <string>
#include <functional>

namespace aio
{
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowSpecifications
	{
		const char* title;
		uint32_t width;
		uint32_t height;
		bool vSync = true;

		EventCallbackFn eventCallback;
	};

	class Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Init() = 0;

		virtual void PollEvents() = 0;
		virtual void Update() = 0;

		virtual void* GetHandle() const = 0;

		virtual void SwapChain() = 0;

		WindowSpecifications& GetSpecs() { return mSpecs; }
		GraphicsContext* GetContext() const{ return mGraphicsContext.get(); }

		static Scope<Window> Create(const WindowSpecifications& windowSpec);
	protected:
		WindowSpecifications mSpecs;
		Scope<GraphicsContext> mGraphicsContext;
	};
}