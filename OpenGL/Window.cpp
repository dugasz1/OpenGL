#include "Window.hpp"




void Window::errorCallback(int error, const char* description) {
	std::cout << "ERROR: " << description << std::endl;
}

Window::Window(std::string title, int width, int height, bool vSync) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->vSync = vSync;
	this->resized = false;
}

void Window::init() {
	glfwSetErrorCallback(&Window::errorCallback);

	if (!glfwInit()) {
		std::cout << "ERROR: Can't init glfw" << std::endl;
	}

	glfwDefaultWindowHints(); // optional, the current window hints are already the default
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);

	if (&this->window == NULL) {
		std::cout << "ERROR: Can't open window" << std::endl;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetWindowSizeCallback TODO

	//glfwSetKeyCallback TODO
	//glfwSetKeyCallback(window, key_callback);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//Center TODO
	//glfwSetWindowPos(window, (vidmode->width() - this->width));

	glfwMakeContextCurrent(window);

	if (isvSync()) {
		// Enable v-sync
		glfwSwapInterval(1);
	}

	glfwShowWindow(window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::setClearColor(float r, float g, float b, float alpha) {
	glClearColor(r, g, b, alpha);
}

bool Window::isKeyPressed(int keyCode) {
	return glfwGetKey(this->window, keyCode) == GLFW_PRESS;
}

bool Window::windowShouldClose() {
	return glfwWindowShouldClose(this->window);
}

std::string Window::getTitle() {
	return this->title;
}

int Window::getWidth() {
	return this->width;
}

int Window::getHeight() {
	return this->height;
}

bool Window::isResized() {
	return this->resized;
}

void Window::setResized(bool resized) {
	this->resized = resized;
}

bool Window::isvSync() {
	return this->vSync;
}

void Window::setvSync(bool vSync) {
	this->vSync = vSync;
}

void Window::update() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

glm::fmat4 Window::GetProjectionMatrix() {
	float aspectRation = (this->width / this->height);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRation, 0.1f, 100.f);
	return projectionMatrix;
}