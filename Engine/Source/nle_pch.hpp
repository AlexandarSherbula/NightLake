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

#ifdef NLE_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <comdef.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
	#include <wrl/client.h>
#endif // NLE_WINDOWS