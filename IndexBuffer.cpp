#include "IndexBuffer.h"

// Constructor that generates a Elements Buffer Object and links it to indices
IndexBuffer::IndexBuffer(std::vector<GLuint>& _indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
}

// Binds the EBO
void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void IndexBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
}
