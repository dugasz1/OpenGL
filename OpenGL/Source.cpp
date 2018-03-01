//#define THREADED

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <thread>
#include "TexturePool.hpp"
#include "Console.hpp"
#include "Window.hpp"
#include "ShaderProgram.hpp"
#include "Renderer.hpp"
#include "MeshPool.hpp"
#include "mesh.h"
#include "Texture2D.hpp"
#include "Object.hpp"
#include "LuaScript.hpp"

double lastX;
double lastY;
bool isInitedXY = false;

Camera* c;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		c->MoveLeft(0.5);
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		c->MoveRight(0.5);
	}
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		c->MoveForeward(0.5);
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		c->MoveBackward(0.5);
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		//camera.Rotate(0, 20);
		printf("Le");
		c->MovePosition(glm::fvec3(0, 1, 0));
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		//camera.Rotate(0, -20);
		printf("Fel");
		c->MovePosition(glm::fvec3(0, -1, 0));
	}

	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		//camera.Rotate(0, -20);
		c->Rotate(1.0, 0);
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		//camera.Rotate(0, -20);
		c->Rotate(-1.0, 0);
	}

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (isInitedXY == false) {
		lastX = xpos;// X horizontal
		lastY = abs(ypos);// Y vertical
		isInitedXY = true;
	}
	double diffX = xpos - lastX;
	double diffY = ypos - lastY;
	if (true) { //Diff egér
		diffY *= 1;
		diffX *= 1;
	}
	if (diffX != 0 || diffY != 0) {
		if (c->rot.x >= 30 && c->rot.x <= 330) {
			if (c->rot.x >= 30 && c->rot.x <= 180) {
				if (diffY < 0) {
					c->Rotate(diffX, diffY);
				}
				else {
					c->Rotate(diffX, 0);
				}
			}
			else if (c->rot.x <= 330 && c->rot.x >= 180) {
				if (diffY > 0) {
					c->Rotate(diffX, diffY);
				}
				else {
					c->Rotate(diffX, 0);
				}
			}
			//camera.Rotate(diffX, 0);
		}
		else {
			c->Rotate(diffX, diffY);
		}

	}
	//printf("X: %f DIFF: %f LAST: %f POS: %f \n", camera.rotation.x, diffY, lastY, ypos);
	lastX = xpos;// X horizontal
	lastY = ypos;// Y vertical
}

void openGlMain() {
	Window* w = new Window("hello", 1024, 768, true);
	w->init();
	glfwSetKeyCallback(w->window, key_callback);
	glfwSetCursorPosCallback(w->window, cursor_position_callback);

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}
	c = new Camera(glm::fvec3(0, -8, -5), glm::fvec3(0.7, 51, 0));


	Renderer* renderer = new Renderer(w, c);
	//IRenderable* rable = new Texture2D();
	Object* ground = new Object("objs/ground_2.obj", "textures/ground.png");
	Object* house1 = new Object("objs/house1.obj", "textures/house2.png");
	Object* window1 = new Object("objs/window.obj", "textures/house2.png");
	window1->position = glm::vec3(10.08631, -3.12126, 2.26623);
	window1->rotation = glm::vec3(103.3390, -0.536, 0.0);
	Object* window2 = new Object("objs/window.obj", "textures/house2.png");
	//Object* house2 = new Object("objs/house2.obj", "textures/house2.png");

	renderer->AddToQueue(ground);
	renderer->AddToQueue(house1);
	renderer->AddToQueue(window1);
	renderer->AddToQueue(window2);
	//renderer->AddToQueue(house2);

	LuaScript::renderer = renderer;
	LuaScript ls("scripts/resource1/");
	/*Model* m = new Model();
	m->LoadModel("objs/plan.obj");*/

	//renderer->models.push_back(m);
	//Texture* t = TexturePool::GetTexture("textures/ground.png");
	//Texture* t2 = TexturePool::GetTexture("textures/ground.png"); // works af

	Console::WriteLine("Hello world", Color::dark_yellow);

	//Mesh* mesh = MeshPool::GetMesh("objs/ground_2.obj");
	//Mesh* mesh2 = MeshPool::GetMesh("objs/ground_2.obj");

	while (!w->windowShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		w->setClearColor(0.3, 0.6, 0.6, 0.0);

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, t->id);

		renderer->Render();
		//mesh->Draw();

		w->update();
	}
	glfwTerminate();
}

int main() {

#ifdef THREADED
	std::thread openglThread(openGlMain);

	while (true)
	{
		std::string input;
		std::getline(std:cin, str);
		std::cout << "Input was: " << input <<std::endl;

		if (!input.compare("exit")) {
			Console::WriteLine("Closing...", Color::dark_red);
			break;
		}
		if (!input.compare("reset")) {
			//TODO restart game
		}
		//restart scripts
	}

	openglThread.join();
#else
	openGlMain();
#endif

	return 0;
}