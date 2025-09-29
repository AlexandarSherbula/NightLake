#include "nle_pch.hpp"

#include "SDL_Window.hpp"

namespace nle
{
    Window::~Window()
    {
    }

    Scope<Window> Window::Create(const WindowSpecifications& windowSpec)
    {
#if defined (NLE_API_OPENGL)
        return CreateScope<SDL3_Window>(windowSpec);
#endif
        NLE_ASSERT(false, "API has not been selected.\n");
        return nullptr;
    }
}