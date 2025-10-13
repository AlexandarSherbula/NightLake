#pragma once

#include "Window/Window.hpp"

#if defined (AIO_WINDOWS)
#include <Windows.h>

namespace aio
{
	class Win32_Window : public Window
	{
	public:
		Win32_Window(const WindowSpecifications& windowSpec);
		~Win32_Window();
		void Init() override {}
		void PollEvents() override;
		void Update() override {}

		inline void* GetHandle() const override { return mHandle; }

		void SwapBuffers() override;
	private:
		HWND mHandle;
		HINSTANCE m_hInstance;
		const CHAR* mWindowClass;
	};

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::string ResultInfo(HRESULT hr);
}
#else
namespace aio
{
	class Win32_Window : public Window
	{
	public:
		Win32_Window(const WindowSpecifications& windowSpec) {}
		~Win32_Window() {}
		void Init() override {}
		void PollEvents() override {}
		void Update() override {}

		inline void* GetHandle() const override { return nullptr; }

		void SwapChain() override {};
	};
}
#endif