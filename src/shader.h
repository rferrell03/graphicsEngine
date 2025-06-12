#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use();


	
};

