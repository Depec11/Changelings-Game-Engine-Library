#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <format>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class Logger {
public:
	static void Log(std::string s);
	Logger();
	~Logger();
private:
	static std::shared_ptr<Logger> m_instance;
	Logger(const Logger& signal);
	const Logger& operator=(const Logger& signal);
	std::string FormatDateTime();
};
