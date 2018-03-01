#include "ShaderProgram.hpp"

std::string ShaderProgram::LoadShaderCode(const std::string& _filePath) {
	std::ifstream stream(_filePath, std::ifstream::in);
	if (stream.fail()) {
		std::cout << "ERROR: Can't open shader code: " << _filePath.c_str() << std::endl;
		//exit(0);
		return nullptr;
	}
	std::string code((std::istreambuf_iterator<char>(stream)),
		std::istreambuf_iterator<char>());
	//printf("%s\n", code.c_str());
	stream.close();
	return  code;
}

bool ShaderProgram::LocateUniform(std::string _uniformName) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgramId, _uniformName.c_str());
	if (uniformLocation < 0) {
		printf("ERROR: Can't find unifrom: %s\n", _uniformName.c_str());
		return false;
	}
	printf("\tUniform founded: %d | %s\n", uniformLocation, _uniformName.c_str());
	this->unifroms.insert(std::pair<std::string, GLuint>(_uniformName, uniformLocation));
	return true;
}

void ShaderProgram::SetUnifrom(std::string _unifromName, glm::fmat4 _value) {
	if (this->unifroms.find(_unifromName) == this->unifroms.end()) {
		return;
	}
	float buffer[16];
	const float *pSource = (const float*)glm::value_ptr(_value);
	for (int i = 0; i < 16; ++i) {
		buffer[i] = pSource[i];
	}
	
	//printf("Unifrom id: %d\n", unifroms[_unifromName]);
	glUniformMatrix4fv(this->unifroms[_unifromName], 1, false, buffer);
}

void ShaderProgram::SetUnifrom(std::string _unifromName, GLint _value){
	if (this->unifroms.find(_unifromName) == this->unifroms.end()) {
		return;
	}
	glUniform1i(this->unifroms[_unifromName], _value);
}

GLuint ShaderProgram::CreateShader(const std::string& _shaderPath, const int _shaderType) {
	int shaderId = glCreateShader(_shaderType);
	if (shaderId == 0) {
		return 0;
	}
	std::string _shaderCode = this->LoadShaderCode(_shaderPath);
	const GLchar *sources[] = { _shaderCode.c_str() };
	GLint lenghts[] = { _shaderCode.size() };
	glShaderSource(shaderId, 1, sources, 0);
	glCompileShader(shaderId);

	GLint isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			std::cout << *i;

		glDeleteShader(shaderId);
		return 0;
	}


	return shaderId;
}

void ShaderProgram::Use() {
	glUseProgram(this->shaderProgramId);
}


ShaderProgram::ShaderProgram(const std::string& _path)
{
	std::string _vertexCode(_path);
	_vertexCode.append(".vs");
	std::string _fragmentCode(_path);
	_fragmentCode.append(".fs");

	this->shaderProgramId = glCreateProgram();

	this->vertexShaderId = this->CreateShader(_vertexCode, GL_VERTEX_SHADER);
	this->fragmentShaderId = this->CreateShader(_fragmentCode, GL_FRAGMENT_SHADER);
	glAttachShader(this->shaderProgramId, this->vertexShaderId);
	glAttachShader(this->shaderProgramId, this->fragmentShaderId);


	//Link program
	glLinkProgram(this->shaderProgramId);

	GLint isLinked;
	glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		std::vector<GLchar> infoLog(maxLength);

		glGetProgramiv(this->shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);
		glGetProgramInfoLog(this->shaderProgramId, maxLength, &maxLength, &infoLog[0]);

		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			std::cout << *i;

		glDeleteProgram(this->shaderProgramId);
		return; //Throw exception
	}
	glDetachShader(this->shaderProgramId, this->fragmentShaderId);
	glDetachShader(this->shaderProgramId, this->vertexShaderId);

	//Validate program
	glValidateProgram(this->shaderProgramId);

	GLint isValid;
	glGetProgramiv(this->shaderProgramId, GL_VALIDATE_STATUS, &isValid);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		std::vector<GLchar> infoLog(maxLength);

		glGetProgramiv(this->shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);

		glGetProgramInfoLog(this->shaderProgramId, maxLength, &maxLength, &infoLog[0]);

		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			std::cout << *i;

		glDeleteProgram(this->shaderProgramId);
		return; //Throw exception
	}
	printf("\tShader program created succesfully | id: %d\n", this->shaderProgramId);

	//Ennek nem itt a helye, ShaderUniforms
	this->LocateUniform("viewMatrix");
	this->LocateUniform("projectionMatrix");
	this->LocateUniform("texture_sampler");
	this->LocateUniform("modelMatrix");
	return; //Succes
}

ShaderUnifroms::ShaderUnifroms()
{
}

ShaderUnifroms::~ShaderUnifroms()
{
}

void ShaderUnifroms::AddOption(std::string name, glm::fmat4 * _value)
{
}

void ShaderUnifroms::AddOption(std::string name, GLint * value)
{
}

void ShaderUnifroms::ApplyPreUniforms()
{
}

void ShaderUnifroms::ApplyUnifroms()
{
}
