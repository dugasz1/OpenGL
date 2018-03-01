#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <iostream>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Window {
private:
	std::string title;
	int width;
	int height;
	
	bool resized;
	bool vSync;

	static void errorCallback(int error, const char* description);
public:
	GLFWwindow* window;
	Window(std::string title, int width, int height, bool vSync);
	void init();
	void setClearColor(float r, float g, float b, float alpha);
	bool isKeyPressed(int keyCode);
	bool windowShouldClose();
	std::string getTitle();
	int getWidth();
	int getHeight();
	bool isResized();
	void setResized(bool resized);
	bool isvSync();
	void setvSync(bool vSync);
	void update();
	glm::fmat4 GetProjectionMatrix();
};

#endif