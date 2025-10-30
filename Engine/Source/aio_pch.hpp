#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <filesystem>
#include <random>
#include <algorithm>
#include <functional>

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Utils/Log.hpp"
#include "Utils/Utilities.hpp"

#include "glad/glad.h"
#define SDL_MAIN_HANDLED 1
#include "SDL3/SDL.h"

#ifdef AIO_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <comdef.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
	#include <dxgi.h>
	#include <wrl/client.h>
	#include <dwmapi.h>
#endif // AIO_WINDOWS