#include "Renderer.hpp"

Renderer::Renderer(Window* _window, Camera* _camera)
{
	this->window = _window;
	this->camera = _camera;

	this->CreateDefaultShaders();
}

Renderer::~Renderer()
{
}

void Renderer::CreateDefaultShaders() {
	/*ShaderProgram* s = ShaderPool::GetShader("shaders/default");
	s->LocateUniform("viewMatrix");
	s->LocateUniform("projectionMatrix");
	s->LocateUniform("texture_sampler");

	ShaderProgram* s2 = ShaderPool::GetShader("shaders/default");

	this->shaders.insert(std::pair<std::string, ShaderProgram*>("default", s));*/
}

void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render() {
	this->Clear(); //Clean page

	/*ShaderProgram* s = this->shaders.at("default");

	s->Use();

	s->SetUnifrom("projectionMatrix", this->window->GetProjectionMatrix());
	s->SetUnifrom("viewMatrix", this->camera->GetViewMatrix());
	s->SetUnifrom("texture_sampler", 0);*/
	//Render skybox
	

	//Render models
	/*for (this->modelRenderIt = this->models.begin(); this->modelRenderIt != this->models.end(); ++this->modelRenderIt) {
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, (*this->modelRenderIt)->t->id);
		(*this->modelRenderIt)->Draw();
	}*/

	//Render HUD TODO
	for (this->shaderIt = this->queue.begin();  this->shaderIt != this->queue.end(); this->shaderIt++) {
		ShaderProgram* s = this->shaderIt->first;
		std::unordered_map<Texture*, std::vector<IRenderable*>>* tQueue = &this->shaderIt->second;
		s->Use();

		for (this->textureIt = tQueue->begin(); this->textureIt != tQueue->end(); this->textureIt++) {
			Texture* t = this->textureIt->first;
			std::vector<IRenderable*>* rQueue = &this->textureIt->second;
			//t->Bind();

			if (!rQueue->empty()) {
				IRenderable* first = (*rQueue->begin());
				first->PreDraw(this->window, this->camera);
				for (this->renderableIt = rQueue->begin(); this->renderableIt != rQueue->end(); this->renderableIt++)
				{
					IRenderable* renderable = (*this->renderableIt);
					renderable->Draw();
				}
				first->PostDraw();
			}
			
		}
	}

}

void Renderer::AddToQueue(IRenderable* item) {
	this->queue[item->shaderProgram][item->texture].push_back(item);
}