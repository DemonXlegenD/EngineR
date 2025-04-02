#pragma once

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBuffer
{
public : 
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VertexBuffer(std::vector<Vertex>& _vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();

};

#endif