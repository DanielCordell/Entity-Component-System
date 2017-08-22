#pragma once
#include <map>

class Logger final {
public:
	enum Level{
		INFO,
		WARNING, //Something might be wrong but won't affect gameplay.
		ERROR, //Something is wrong, and it's gonna affect gameplay.
		FATAL, //ABORT ABORT
	};

	static void Log(std::string log);
	static void Log(Level level, std::string log);
	static void NewLine();
	static void Div(char divider);
private:
	static std::map<Level, std::string> logtype;
};
