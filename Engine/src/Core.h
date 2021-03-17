#pragma once
// WINDOWS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// EVERITH
#include "Everith\Log\Log.h"
#include "Everith/Core.h"

#ifdef EVE_PLATFORM_WINDOWS
#include <Windows.h>
#endif // EVE_PLATFORM_WINDOWS

#define GLEW_STATIC
#define _CRT_SECURE_NO_DEPRECATE

//#define _UNICODE
//#define NOMINMAX
//#define UNICODE

//Headers
#include "Log\Log.h"
#include "Config.h"

//#include <winsock2.h>

//MACROS
#ifdef EVE_ENABLE_ASSERTS
#define EVE_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define EVE_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define EVE_ASSERT(x, ...)
#define EVE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
