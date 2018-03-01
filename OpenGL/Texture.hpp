#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "SOIL\SOIL.h"
#include <iostream>
#include <fstream>
#include <GL\glew.h>

typedef GLubyte PixelRGB[3];

class Texture
{
private:
	PixelRGB* texturePixels;
	int width, height;
public:
	GLuint id;

	Texture(std::string _file_path);
	~Texture();
	void LoadTexture(std::string _file_path);
	void Bind();
};

#endif