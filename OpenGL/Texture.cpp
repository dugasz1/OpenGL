#include "Texture.hpp"

Texture::Texture(std::string _file_path)
{
	this->LoadTexture(_file_path);
}

Texture::~Texture()
{
}

void Texture::LoadTexture(std::string _file_path)
{
	std::ifstream f(_file_path.c_str());
	if (f.fail()) {
		printf("ERROR: can't load texture: %s\n", _file_path.c_str());
		return;
	}
	f.close();
	
	this->texturePixels = NULL;
	
	this->texturePixels = (PixelRGB*)SOIL_load_image(_file_path.c_str(), &this->width, &this->height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &this->id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->texturePixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	std::cout << "\t" << _file_path << " texture loaded succesfully.\n";

	SOIL_free_image_data((unsigned char *)this->texturePixels);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, this->id);
}