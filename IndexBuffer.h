#pragma once

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class IndexBuffer
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	IndexBuffer(GLuint* _indices, GLsizeiptr _size);

	void Bind();
	void Unbind();
	void Delete();

};

#endif