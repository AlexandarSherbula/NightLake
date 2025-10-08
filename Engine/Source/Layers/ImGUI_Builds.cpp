#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_sdl3.cpp>
#include <backends/imgui_impl_opengl3.cpp>

#if defined (NLE_WINDOWS)
#include <backends/imgui_impl_win32.cpp>
#include <backends/imgui_impl_dx11.cpp>
#endif // AIO_PLATFORM_WINDOWS