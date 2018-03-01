#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>


class ShaderUnifroms { //TODO
private:
	std::unordered_map <std::string, glm::fmat4*> fmat4Options;
	std::unordered_map <std::string, GLint*> glintOptions;
public:
	ShaderUnifroms();
	~ShaderUnifroms();

	void AddOption(std::string name, glm::fmat4* _value);
	void AddOption(std::string name, GLint* value);

	void ApplyPreUniforms(); 
	void ApplyUnifroms();
};

class ShaderProgram {
private:
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
	GLuint shaderProgramId;
	std::map<std::string, GLuint> unifroms;

	std::string LoadShaderCode(const std::string& _filePath);
	GLuint CreateShader(const std::string& _shaderPath, const int _shaderType);
public:
	ShaderProgram(const std::string& _path);
	~ShaderProgram();
	//static ShaderProgram* LoadShaderProgram(const std::string& _vertexCode, const std::string& _fragmentCode);
	bool LocateUniform(std::string _uniformName);
	void SetUnifrom(std::string _unifromName, glm::fmat4 _value);
	void SetUnifrom(std::string _unifromName, GLint _value);
	void Use();
};

#endif