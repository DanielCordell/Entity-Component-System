#include "Includes/logger.h"

int main() {
	Logger::Log(Logger::ERROR, "Test");
	Logger::Log(Logger::FATAL, "OHNOBADNESS");
	Logger::Log(Logger::INFO, "isokainow");
	Logger::Div('*');
	Logger::NewLine();
	Logger::Log("YEAH BOI");
}