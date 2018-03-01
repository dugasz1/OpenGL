#include "Console.hpp"

#if defined(_WIN32) || defined(_WIN64)
HANDLE Console::consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

Console::Console() {}

Console::~Console() {}

void Console::WriteLine(std::string msg, Color color)
{
	#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(Console::consoleHandler, color);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(Console::consoleHandler, Color::light_gray); //reset
	#else
	std::cout << msg << std::endl;
	#endif
}

void Console::Write(std::string msg, Color color) {
#if defined(_WIN32) || defined(_WIN64)
	SetConsoleTextAttribute(Console::consoleHandler, color);
	std::cout << msg;
	SetConsoleTextAttribute(Console::consoleHandler, Color::light_gray); //reset
#else
	std::cout << msg;
#endif
}