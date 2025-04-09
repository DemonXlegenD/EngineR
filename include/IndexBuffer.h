#pragma once

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class IndexBuffer
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	IndexBuffer(std::vector<GLuint>& _indices);

	void Bind();
	void Unbind();
	void Delete();

};

#endif