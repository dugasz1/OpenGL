#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <map>
#include <unordered_map>
#include <GL\glew.h>
#include "Window.hpp"
#include "Camera.hpp"
#include "ShaderPool.hpp"
#include "Texture.hpp"

#define interface class

interface IRenderable {
public:
	ShaderUnifroms* shaderUnifroms;
	ShaderProgram* shaderProgram;
	Texture* texture;

	virtual void PreDraw(Window* window, Camera* camera) = 0;
	virtual void Draw() = 0;
	virtual void PostDraw() = 0;
};

class Renderer
{
private:
	Window* window;
	Camera* camera;

	std::map<std::string, ShaderProgram*> shaders;
	std::vector<IRenderable*>::iterator modelRenderIt;

	std::unordered_map<ShaderProgram*, std::unordered_map<Texture*, std::vector<IRenderable*>> > queue;

	std::unordered_map<ShaderProgram*, std::unordered_map<Texture*, std::vector<IRenderable*>>>::iterator shaderIt;
	std::unordered_map<Texture*, std::vector<IRenderable*>>::iterator textureIt;
	std::vector<IRenderable*>::iterator renderableIt;
	

	void CreateDefaultShaders();
public:
	std::vector<IRenderable*> models;

	Renderer(Window* _window, Camera* _camera);
	~Renderer();
	void AddToQueue(IRenderable * item);
	void Clear();
	void Render();

};



#endif 