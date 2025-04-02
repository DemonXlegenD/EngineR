#include"Model.h"
#include "Texture.h"


Model::Model(const std::string& _path) {
    LoadModel(_path);
}

void Model::Draw(Shader& _shader, Camera& _camera, glm::vec3 _translation, glm::quat _rotation, glm::vec3 _scale)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(_shader, _camera, glm::mat4(1.0f),  _translation, _rotation, _scale);
}

void Model::LoadModel(const std::string& _path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Erreur Assimp : " << importer.GetErrorString() << std::endl;
        return;
    }
    directory = _path.substr(0, _path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* _mesh, const aiScene* _scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = _mesh->mVertices[i].x;
        vector.y = _mesh->mVertices[i].y;
        vector.z = _mesh->mVertices[i].z;
        vertex.position = vector;
        vector.x = _mesh->mNormals[i].x;
        vector.y = _mesh->mNormals[i].y;
        vector.z = _mesh->mNormals[i].z;
        vertex.normal = vector;

        if (_mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = _mesh->mTextureCoords[0][i].x;
            vec.y = _mesh->mTextureCoords[0][i].y;
            vertex.texUV = vec;
        }
        else
            vertex.texUV = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
    {
        aiFace face = _mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
        // process material
    if (_mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,
            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material,
            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* _mat, aiTextureType _type, std::string _typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
    {
        aiString str;
        _mat->GetTexture(_type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (skip) continue;

        Texture texture(str.C_Str(), _typeName.c_str()  , i, directory);
        texturesLoaded.push_back(texture);
        textures.push_back(texture);
    }
    return textures;
}