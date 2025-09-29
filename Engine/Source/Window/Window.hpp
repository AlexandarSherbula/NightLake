#pragma once

#include "Core/Utilities.hpp"

#include <string>

namespace nle
{
	struct WindowSpecifications
	{
		std::string title;
		uint32_t width;
		uint32_t height;
		bool vSync = true;
	};

	class Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Initialize() = 0;

		virtual void PollEvents() = 0;

		virtual void* GetHandle() const = 0;

		static Scope<Window> Create(const WindowSpecifications& windowSpec);
	protected:
		virtual void EventCallbacks() = 0;
	protected:
		WindowSpecifications mSpecs;
	};
}