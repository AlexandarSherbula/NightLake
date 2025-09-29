#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <random>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Log.hpp"
#include "Core/Utilities.hpp"

#include "glad/glad.h"
#define SDL_MAIN_HANDLED 1
#include "SDL3/SDL.h"

#ifdef NLE_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <comdef.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
	#include <wrl/client.h>
#endif // NLE_WINDOWS