#include "Includes/logger.h"
#include <iostream>

void Logger::Log(std::string log) {
	std::cout << log << std::endl;
}

void Logger::Log(Level level, std::string log) {
	std::cout << logtype[level] << log << std::endl;
}

void Logger::NewLine() {
	Log("");
}

void Logger::Div(char divider) {
	Log(std::string(40, divider));
}

std::map<Logger::Level, std::string> Logger::logtype = {
	{ ERROR, "    [Error] " },
	{ FATAL, "    [FATAL] " },
	{ WARNING, "    [Warning] " },
	{ INFO, "    [Info] " }
};
