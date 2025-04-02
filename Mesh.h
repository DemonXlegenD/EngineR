#pragma once

#include <string>
#include <vector>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VertexArray VAO;

	Mesh(std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices, std::vector<Texture>& _textures);

	void Draw
	(
		Shader& _shader,
		Camera& _camera,
		glm::mat4 _matrix = glm::mat4(1.0f),
		glm::vec3 _translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};

