#include "VertexArray.h"

// Constructor that generates a VAO ID
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VertexArray::LinkAttrib(VertexBuffer& _vertexBuffer, GLuint _layout, GLuint _numComponents, GLenum _type, GLsizeiptr _stride, void* _offset)
{
	_vertexBuffer.Bind();

	glVertexAttribPointer(_layout, _numComponents, _type, GL_FALSE, _stride , _offset);
	glEnableVertexAttribArray(_layout);
	_vertexBuffer.Unbind();
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
