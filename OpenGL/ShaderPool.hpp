#ifndef SHADERPOOL_HPP
#define SHADERPOOL_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "ShaderProgram.hpp"
#include "Console.hpp"

class ShaderPool {
private:
	static std::unordered_map<std::string, ShaderProgram*> pool;

	ShaderPool();
public:
	~ShaderPool();
	
	static ShaderProgram* GetShader(std::string path);
};


#endif