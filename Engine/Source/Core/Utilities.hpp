#pragma once

#include <memory>

#define BIT(x) (1 << x)

#if defined NLE_WINDOWS
	#define NLE_API_DX11
#endif

#if !defined(NLE_WINDOWS) && defined (NLE_API_DX11)
#error  DirectX11 is only supported on Windows
#endif

// Supported on both Windows and Linux
#define NLE_API_OPENGL

#define NLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace nle
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}