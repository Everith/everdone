#pragma once

#include "..\Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace  Everith {
	class Log {
	public:
		Log();
		// TODO remove init if nott nedden static function insted of constructor
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//CORE LOG MACROS
#define EVE_CORE_INFO(...) Everith::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EVE_CORE_PASS(...)  Everith::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EVE_CORE_WARN(...)  Everith::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EVE_CORE_ERROR(...) Everith::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EVE_CORE_FATAL(...) Everith::Log::GetCoreLogger()->critical(__VA_ARGS__)

//CLIENT LOG MACROS
#define EVE_INFO(...)		Everith::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EVE_PASS(...)		Everith::Log::GetClientLogger()->info(__VA_ARGS__)
#define EVE_WARN(...)		Everith::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EVE_ERROR(...)		Everith::Log::GetClientLogger()->error(__VA_ARGS__)
#define EVE_FATAL(...)		Everith::Log::GetClientLogger()->critical(__VA_ARGS__)
