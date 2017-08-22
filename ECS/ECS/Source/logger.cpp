#include <iostream>
#include <string>

#include "Includes/logger.h"

//Fancy console colours if not on windows RIP
#ifndef _WIN32
#define RESET   "\033[0m"
#define FATALCOLOR     "\033[1m\033[31m"
#define ERRORCOLOR  "\033[1m\033[33m"
#define INFOCOLOR   "\033[1m\033[32m"
#else
#define RESET
#define ERRORCOLOR
#define FATALCOLOR
#define INFOCOLOR
#endif

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
	Log(std::string(60, divider));
}

std::map<Logger::Level, std::string> Logger::logtype = {
	{ ERROR, ERRORCOLOR "[Error]\t" RESET },
	{ FATAL, FATALCOLOR "[Fatal]\t" RESET },
	{ WARNING, ERRORCOLOR "[Warn]\t" RESET },
	{ INFO, INFOCOLOR "[Info]\t" RESET }
};
