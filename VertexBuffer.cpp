#include "VertexBuffer.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VertexBuffer::VertexBuffer(std::vector<Vertex>& _vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);
}

// Binds the VBO
void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VertexBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
}
