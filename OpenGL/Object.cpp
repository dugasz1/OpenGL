#include "Object.hpp"

Object::Object(std::string meshPath, std::string texturePath, std::string shaderPath) {
	this->shaderProgram = ShaderPool::GetShader(shaderPath);

	this->texture = TexturePool::GetTexture(texturePath);
	this->mesh = MeshPool::GetMesh(meshPath);

}

Object::~Object() {}

void Object::PreDraw(Window* window, Camera* camera)
{
	//Don't depends on instance (few uniforms)
	this->shaderProgram->SetUnifrom("projectionMatrix", window->GetProjectionMatrix());
	this->shaderProgram->SetUnifrom("viewMatrix", camera->GetViewMatrix());
	this->shaderProgram->SetUnifrom("texture_sampler", 0);

	glActiveTexture(GL_TEXTURE0);
	this->texture->Bind();
}

void Object::Draw() {
	glm::fmat4 modelMatrix(1.0f);
	//glm::scale()
	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, this->position);
	this->shaderProgram->SetUnifrom("modelMatrix", modelMatrix);
	this->mesh->Draw();
	//this->shaderProgram->SetUnifrom("objectMatrix") //Unifroms that depend on instance
}

void Object::PostDraw()
{
	//Clean up
}
