#include "logger.h"

void Logger::Log(std::string s) {
	std::cout << "[" << m_instance->FormatDateTime() << "] " << s << std::endl;
}
Logger::Logger() {
	Log("STARTING LOGGER!");
}
Logger::~Logger() {
	Log("ENDING LOGGER!");
}
Logger::Logger(const Logger& signal) {}
const Logger& Logger::operator=(const Logger& signal) {
	return *m_instance;
}
std::string Logger::FormatDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_c);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%y-%m-%d %H:%M:%S");
    return ss.str();
}
std::shared_ptr<Logger> Logger::m_instance = std::make_shared<Logger>();
