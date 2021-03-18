#pragma once

#include <SpringEngine/core.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace SE
{
	enum SE_API LOG_LVL
	{
		SE_LOGLVL_TRACE = SPDLOG_LEVEL_TRACE,
		SE_LOGLVL_INFO = SPDLOG_LEVEL_INFO,
		SE_LOGLVL_WARN = SPDLOG_LEVEL_WARN,
		SE_LOGLVL_ERROR = SPDLOG_LEVEL_ERROR,
		SE_LOGLVL_CRITICAL = SPDLOG_LEVEL_CRITICAL
	};
	class SE_API Log
	{
	public:
		static void init();
		
		static void setCoreLogLevel(SE::LOG_LVL logLevel);
		static void setAppLogLevel(SE::LOG_LVL logLevel);

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return sm_coreLogger; };
		inline static std::shared_ptr<spdlog::logger>& getAppLogger() { return sm_appLogger; };
	private:
		static std::shared_ptr<spdlog::logger> sm_coreLogger;
		static std::shared_ptr<spdlog::logger> sm_appLogger;
	};
}

#ifndef NDEBUG
#define SE_CORE_TRACE(...)            ::SE::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SE_CORE_INFO(...)             ::SE::Log::getCoreLogger()->info(__VA_ARGS__)
#define SE_CORE_WARN(...)             ::SE::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SE_CORE_ERROR(...)            ::SE::Log::getCoreLogger()->error(__VA_ARGS__)
#define SE_CORE_CRITICAL(...)         ::SE::Log::getCoreLogger()->critical(__VA_ARGS__)

#define SE_CORE_LOG_LEVEL(logLvl)     ::SE::Log::setCoreLogLevel(logLvl)


#define SE_TRACE(...)                 ::SE::Log::getAppLogger()->trace(__VA_ARGS__)
#define SE_INFO(...)                  ::SE::Log::getAppLogger()->info(__VA_ARGS__)
#define SE_WARN(...)                  ::SE::Log::getAppLogger()->warn(__VA_ARGS__)
#define SE_ERROR(...)                 ::SE::Log::getAppLogger()->error(__VA_ARGS__)
#define SE_CRITICAL(...)              ::SE::Log::getAppLogger()->critical(__VA_ARGS__)

#define SE_LOG_LEVEL(...)             ::SE::Log::setAppLogLevel(__VA_ARGS__)

#else
#define SE_CORE_ERROR(...)
#define SE_CORE_WARN(...)
#define SE_CORE_INFO(...)
#define SE_CORE_TRACE(...)
#define SE_CORE_CRITICAL(...)
#define SE_CORE_LOG_LEVEL(...)

#define SE_ERROR(...)
#define SE_WARN(...)
#define SE_INFO(...)
#define SE_TRACE(...)
#define SE_CRITICAL(...)
#define SE_LOG_LEVEL(...)
#endif