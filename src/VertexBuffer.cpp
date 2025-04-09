#include "VertexBuffer.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VertexBuffer::VertexBuffer()
{
	ID = 0;
}

void VertexBuffer::Create()
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::AddData(std::vector<Vertex>& _vertices) {
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
void VertexBuffer::Destroy()
{
	glDeleteBuffers(1, &ID);
}
