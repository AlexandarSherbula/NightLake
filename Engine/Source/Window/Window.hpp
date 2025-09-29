#pragma once

#include "Core/Utilities.hpp"
#include "Events/Events.hpp"

#include <string>
#include <functional>

namespace nle
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
		virtual void Initialize() = 0;

		virtual void PollEvents() = 0;

		virtual void* GetHandle() const = 0;

		WindowSpecifications& GetSpecs() { return mSpecs; }

		static Scope<Window> Create(const WindowSpecifications& windowSpec);
	protected:
		WindowSpecifications mSpecs;
	};
}