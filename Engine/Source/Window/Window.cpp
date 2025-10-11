#include "aio_pch.hpp"

#include "SDL_Window.hpp"
#include "Win32_Window.hpp"

#include "Renderer/Renderer.hpp"

namespace aio
{
    Window::~Window()
    {
    }

    Scope<Window> Window::Create(const WindowSpecifications& windowSpec)
    {
        CHECK_API(
            return CreateScope<SDLWindow>(windowSpec),
            return CreateScope<Win32_Window>(windowSpec)
        );
        AIO_ASSERT(false, "API has not been selected.\n");
        return nullptr;
    }
}