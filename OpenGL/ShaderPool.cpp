#include "ShaderPool.hpp"


std::unordered_map<std::string, ShaderProgram*> ShaderPool::pool;

ShaderPool::ShaderPool() {}

ShaderPool::~ShaderPool() {}

ShaderProgram* ShaderPool::GetShader(std::string path) {
	ShaderProgram* s;
	try {
		s = ShaderPool::pool.at(path);

		Console::Write("Shader: ", Color::light_yellow);
		std::cout << "Founded, pointer returned (" << path << ")" << std::endl;
	}
	catch (const std::exception&) {
		Console::Write("Shader: ", Color::light_yellow);
		std::cout << "Not founded, generating... (" << path << ")" << std::endl;

		s = new ShaderProgram(path);
		std::pair<std::string, ShaderProgram*> pair(path, s);
		ShaderPool::pool.insert(pair);
	}
	return s;
}