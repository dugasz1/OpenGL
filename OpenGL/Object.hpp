#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "glm\glm.hpp"
#include <glm\gtc\matrix_transform.hpp>
#include "Renderer.hpp"
#include "ShaderPool.hpp"
#include "TexturePool.hpp"
#include "MeshPool.hpp"

class Object : public IRenderable
{
private:
	Mesh* mesh;
public:
	glm::vec3 position;
	glm::vec3 rotation;

	Object(std::string meshPath, std::string texturePath, std::string shaderPath = "shaders/default");
	~Object();

	void PreDraw(Window* window, Camera* camera);
	void Draw();
	void PostDraw();

};


#endif
