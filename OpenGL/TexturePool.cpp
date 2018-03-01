#include "TexturePool.hpp"

std::unordered_map<std::string, Texture*> TexturePool::pool;

TexturePool::TexturePool() {}

TexturePool::~TexturePool() {}

Texture* TexturePool::GetTexture(std::string path) {
	Texture* t;
	try {
		t = TexturePool::pool.at(path);

		Console::Write("Texture: ", Color::dark_cyan);
		printf("Founded, pointer returned \n");
	}
	catch (const std::exception&) {
		Console::Write("Texture: ", Color::dark_cyan);
		printf("Not founded, generating.. \n");

		t = new Texture(path);
		std::pair<std::string, Texture*> pair(path, t);
		TexturePool::pool.insert(pair);
	}
	return t;
}