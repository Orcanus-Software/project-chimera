#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <memory>

namespace VTT {
	class Logger {
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& getLogger() { return logger; };
	private:
		static std::shared_ptr<spdlog::logger> logger;
	};
}