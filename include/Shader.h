#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


namespace Engine {

std::string GetFileContents(const char* _filename);

class Shader
{
public : 
	Shader();
	// Build the Shader Program from 2 different shaders
	void Load(const char* _vertexFile, const char* _fragmentFile);

	void Unload();

	void Activate();

	unsigned int GetID() { return ID; }

private : 
	void CompileErrors(unsigned int _shader, const char* _type);

	unsigned int ID;
};


}

