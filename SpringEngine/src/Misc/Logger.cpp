//#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Misc/Logger.hpp>

std::shared_ptr<spdlog::logger> SE::Log::sm_coreLogger;
std::shared_ptr<spdlog::logger> SE::Log::sm_appLogger;

void SE::Log::init()
{
	spdlog::set_pattern("%^[%T] [%=n] %v%$");
	sm_coreLogger = spdlog::stdout_color_mt("ENGINE");
	sm_coreLogger->set_level(spdlog::level::trace);

	sm_appLogger = spdlog::stdout_color_mt("APP");
	sm_appLogger->set_level(spdlog::level::trace);

	SE_CORE_WARN("Logger initialized");
}

void SE::Log::setCoreLogLevel(SE::LOG_LVL logLevel)
{
	sm_coreLogger->set_level((spdlog::level::level_enum)logLevel);
}

void SE::Log::setAppLogLevel(SE::LOG_LVL logLevel)
{
	sm_appLogger->set_level((spdlog::level::level_enum)logLevel);
}
