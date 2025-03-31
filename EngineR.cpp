#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Camera.h"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
    -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

const int width = 800;
const int height = 800;

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Windows Hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW we are using the CORE profile (modern functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800x800 px
    GLFWwindow* window = glfwCreateWindow(width, height, "Engine R", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Loag GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window (!= window)
    glViewport(0, 0, width, height); 

    // Creates Shader object using shaders default.vert and default.frag
    Shader shader_program("default.vert", "default.frag");
    
    //Generates Vertex Array
    VertexArray VAO1;
    VAO1.Bind();

    //Generates Vertex Buffer Object & Index Buffer Object and their links to vertices and to indices
    VertexBuffer VBO1(vertices, sizeof(vertices));
    IndexBuffer EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    Shader light_shader("light.vert", "light.frag");

    VertexArray light_VAO;
    light_VAO.Bind();

    VertexBuffer light_VBO(lightVertices, sizeof(lightVertices));
    IndexBuffer light_EBO(lightIndices, sizeof(lightIndices));

    light_VAO.LinkAttrib(light_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    light_VAO.Unbind();
    light_VBO.Unbind();
    light_EBO.Unbind();


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);


    light_shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(light_shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shader_program.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader_program.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shader_program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    std::string path = std::filesystem::current_path().string() + "\\Resources\\Textures\\" ;

    // Texture
    Texture plank_tex((path + "planks.png").c_str(), GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    plank_tex.TexUnit(shader_program, "tex0", 0);

    Texture planks_spec((path + "planksSpec.png").c_str(), GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planks_spec.TexUnit(shader_program, "tex1", 1);
    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.f, 0.f, 0.f));

    // Main while loop
    while (!glfwWindowShouldClose(window)) {

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.UpdateMatrix(45.0f, 0.1f, 100.0f);



        // Tell OpenGL which Shader Program we want to use
        shader_program.Activate();
        glUniform3f(glGetUniformLocation(shader_program.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);

        camera.Matrix(shader_program, "camMatrix");

        // Binds texture so that is appears in rendering
        plank_tex.Bind();
        planks_spec.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        light_shader.Activate();


        camera.Matrix(light_shader, "camMatrix");
        light_VAO.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the object we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    plank_tex.Delete();
    planks_spec.Delete();
    shader_program.Delete();
    light_VAO.Delete();
    light_VBO.Delete();
    light_EBO.Delete();
    light_shader.Delete();

    // Destroy window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
}
