#pragma once

#include "Core/Utilities.hpp"
#include "Events/Events.hpp"
#include "Input/Input.hpp"

#include <string>
#include <functional>

namespace aio
{
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowSpecifications
	{
		std::string title;
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
		virtual void* GetContext() const = 0;

		virtual void SwapChain() = 0;

		WindowSpecifications& GetSpecs() { return mSpecs; }

		static Scope<Window> Create(const WindowSpecifications& windowSpec);
	protected:
		WindowSpecifications mSpecs;
	};
}