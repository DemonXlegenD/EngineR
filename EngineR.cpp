// EngineR.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"




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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Engine R", NULL, NULL);

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
    glViewport(0, 0, 800, 800); 

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Upper triangle
        5, 4, 1 // Lower right triangle
    };

    // Creates Shader object using shaders default.vert and default.frag
    Shader shader_program("default.vert", "default.frag");
    
    //Generates Vertex Array
    VertexArray VAO1;
    VAO1.Bind();

    //Generates Vertex Buffer Object & Index Buffer Object and their links to vertices and to indices
    VertexBuffer VBO1(vertices, sizeof(vertices));
    IndexBuffer EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVertexBuffer(VBO1, 0);

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // Main while loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shader_program.Activate();
        
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        //Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents(); // Process the Events
    }

    // Delete all the object we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shader_program.Delete();

    // Destroy window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
    std::cout << "Hello World!\n";
}
