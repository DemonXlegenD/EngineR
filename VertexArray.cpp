#include "VertexArray.h"

// Constructor that generates a VAO ID
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VertexArray::LinkVertexBuffer(VertexBuffer _vbo, GLuint _layout)
{
	_vbo.Bind();

	glVertexAttribPointer(_layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(_layout);
	_vbo.Unbind();
}

// Binds the VAO
void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
