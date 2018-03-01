#ifndef TEXTUREPOOL_HPP
#define TEXTUREPOOL_HPP

#include <string>
#include <unordered_map>
#include "Texture.hpp"
#include "Console.hpp"

class TexturePool {
private:
	TexturePool();

	static std::unordered_map<std::string, Texture*> pool;
public:
	~TexturePool();

	static Texture* GetTexture(std::string path);
};

#endif