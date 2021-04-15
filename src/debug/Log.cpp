#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace VTT
{
	std::shared_ptr<spdlog::logger> Logger::logger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;

		/*auto error_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		error_sink->set_level(spdlog::level::err);
		*/
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::info);
		
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/latest.log", true);
		console_sink->set_level(spdlog::level::trace);

		//logSinks.emplace_back(error_sink);
		logSinks.emplace_back(console_sink);
		logSinks.emplace_back(file_sink);

		logger = std::make_shared<spdlog::logger>("VTT", begin(logSinks), end(logSinks));
		spdlog::register_logger(logger);

		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
	}
}