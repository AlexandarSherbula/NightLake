#pragma once

#include <memory>
#include <string>

#define BIT(x) (1 << x)

#if defined(NLE_WINDOWS)

#define CHECK_API(x, y)                                           \
        do {                                                      \
            switch (Application::Get().GetRenderingAPI_Flag()) {  \
                case OpenGL: { x; break; }                        \
                case DX11:   { y; break; }                        \
            }                                                     \
        } while(0)
#else
#define CHECK_API(x, y) do { x; } while(0)
#endif

#define NLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

enum RenderAPI_Flag
{
	OpenGL,
	DX11
};

inline std::wstring StringToWide(const std::string& str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}

inline std::string WideToString(const std::wstring& wstr)
{
	std::string str(wstr.begin(), wstr.end());
	return str;
}

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