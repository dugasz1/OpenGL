#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <string>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#endif

enum Color {
	black,          //  0 text color - multiply by 16, for background colors
	dark_blue,      //  1
	dark_green,     //  2
	dark_cyan,      //  3
	dark_red,       //  4
	dark_magenta,   //  5
	dark_yellow,    //  6
	light_gray,     //  7
	dark_gray,      //  8
	light_blue,     //  9
	light_green,    // 10
	light_cyan,     // 11
	light_red,      // 12
	light_magenta,  // 13
	light_yellow,   // 14
	white           // 15
};

class Console
{
private:
	#if defined(_WIN32) || defined(_WIN64)
	static HANDLE consoleHandler;
	#endif
	Console();
public:
	~Console();
	static void WriteLine(std::string msg, Color color = Color::light_gray);
	static void Write(std::string msg, Color color = Color::light_gray);
};


#endif