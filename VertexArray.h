#pragma once

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray
{
public : 
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VertexArray();

	// Links a VBO to the VAO using a certain layout
	void LinkVertexBuffer(VertexBuffer _vbo, GLuint _layout);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif

