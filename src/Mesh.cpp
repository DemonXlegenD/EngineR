#include "Mesh.h"

namespace Engine {
    Mesh::Mesh(std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices, std::vector<Texture>& _textures)
    {
        vertices = _vertices;
        indices = _indices;
        textures = _textures;

        VAO.Bind();

        //Generates Vertex Buffer Object & Index Buffer Object and their links to vertices and to indices
        VertexBuffer VBO;
        VBO.Create();
        VBO.AddData(vertices);
        IndexBuffer EBO(indices);

        // Links VBO attributes such as coordinates and colors to VAO
        VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
        VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
        VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
        VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

        VAO.Unbind();
        VBO.Unbind();
        EBO.Unbind();
    }

    void Mesh::Draw(Shader& _shader, Camera& _camera, glm::mat4 _matrix, glm::vec3 _translation, glm::quat _rotation, glm::vec3 _scale)
    {
        _shader.Activate();
        VAO.Bind();

        unsigned int num_diffuse = 0;
        unsigned int num_specular = 0;

        for (unsigned int i = 0; i < textures.size(); i++) {
            std::string num;
            std::string type = textures[i].type;

            if (type == "diffuse") {
                num = std::to_string(num_diffuse++);
            }
            else if (type == "specular") {
                num = std::to_string(num_specular++);
            }
            textures[i].TexUnit(_shader, (type + num).c_str(), i);
            textures[i].Bind();
        }
        glUniform3f(glGetUniformLocation(_shader.GetID(), "camPos"), _camera.position.x, _camera.position.y, _camera.position.z);
        _camera.Matrix(_shader, "camMatrix");

        // Initialize matrices
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        // Transform the matrices to their correct form
        trans = glm::translate(trans, _translation);
        rot = glm::mat4_cast(_rotation);
        sca = glm::scale(sca, _scale);

        // Push the matrices to the vertex shader
        glUniformMatrix4fv(glGetUniformLocation(_shader.GetID(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(_shader.GetID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
        glUniformMatrix4fv(glGetUniformLocation(_shader.GetID(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
        glUniformMatrix4fv(glGetUniformLocation(_shader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(_matrix));

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    }
}