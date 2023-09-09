#include "Shader.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <iostream>
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	this->vertexPath = (GLchar*)vertexPath;
	this->fragmentPath = (GLchar*)fragmentPath;
}
Shader::Shader(GLboolean compile, const GLchar* vertexPath, const GLchar* fragmentPath)
{
	this->vertexPath = (GLchar*)vertexPath;
	this->fragmentPath = (GLchar*)fragmentPath;
	if (compile) Compile();
}
Shader::~Shader(){}
void Shader::Use()
{
	glUseProgram(this->program);
}
void Shader::Compile()
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar info[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info << std::endl;
	}

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, info);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}