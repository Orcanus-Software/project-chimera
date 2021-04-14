#include "Log.h"

namespace VTT {
	class Logger {
	public:
		std::shared_ptr<spdlog::logger> getLogger();
	private:
		std::shared_ptr<spdlog::logger> logger;
	};
}