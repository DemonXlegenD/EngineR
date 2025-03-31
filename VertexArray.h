#pragma once

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "VertexBuffer.h"

class VertexArray
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VertexArray();

	/* Links a VBO Attribute such as a position or color to the VAO
	*
	*  _stride : distance in bytes between the beginning of one vertex to the beginning of the new one
	*/ 
	void LinkAttrib(VertexBuffer& _vertexBuffer, GLuint _layout, GLuint _numComponents, GLenum _type, GLsizeiptr _stride, void* _offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif