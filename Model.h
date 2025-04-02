#pragma once

#include <json.hpp>
#include "Mesh.h"

#include<assimp/scene.h>
#include<assimp/Importer.hpp>
#include <assimp/postprocess.h>

using json = nlohmann::json;

class Model
{
public:
	glm::vec3 position;
	glm::vec3 size;

	Model(const std::string& _path);

	void Draw(
		Shader& _shader,
		Camera& _camera,
		glm::vec3 _translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

protected:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> texturesLoaded;

	void LoadModel(const std::string& _path);
	void ProcessNode(aiNode* _node, const aiScene* _scene);
	Mesh ProcessMesh(aiMesh* _mesh, const aiScene* _scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* _mat, aiTextureType _type, std::string _typeName);
};

