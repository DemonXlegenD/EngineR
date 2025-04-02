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

#include "Model.h"

const int width = 800;
const int height = 800;

// Takes care of the information needed to draw the windows
const unsigned int numWindows = 100;
glm::vec3 positionsWin[numWindows];
float rotationsWin[numWindows];

// Takes care of drawing the windows in the right order
unsigned int orderDraw[numWindows];
float distanceCamera[numWindows];

// Compare function
int compare(const void* a, const void* b)
{
    double diff = distanceCamera[*(int*)b] - distanceCamera[*(int*)a];
    return  (0 < diff) - (diff < 0);
}

std::string directory_path = std::filesystem::current_path().string();
std::string resources_path = directory_path + "\\Resources\\";

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

    // Generates Shader object using shaders default.vert and default.frag
    Shader shader_program("default.vert", "default.frag");
    Shader shader_grass_program("default.vert", "grass.frag");
    Shader shader_window_program("default.vert", "window.frag");

    Shader outlining_shader_program("outlining.vert", "outlining.frag");

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shader_program.Activate();
    glUniform4f(glGetUniformLocation(shader_program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    shader_grass_program.Activate();
    glUniform4f(glGetUniformLocation(shader_grass_program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_grass_program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    shader_window_program.Activate();
    glUniform4f(glGetUniformLocation(shader_window_program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_window_program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
    // Enables the Stencil Buffer
    glEnable(GL_STENCIL_TEST);
    // Sets rules for outcomes of stecil tests
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  

    // Enables Cull Facing
    glEnable(GL_CULL_FACE);
    // Keeps front faces
    glCullFace(GL_BACK);
    // Uses clock-wise standard
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera(width, height, glm::vec3(0.f, 0.f, 0.f));

    Model grass((resources_path + "Models/grass/scene.gltf").c_str());
    Model ground((resources_path + "Models/ground/scene.gltf").c_str());
    Model windows((resources_path + "Models/window/scene.gltf").c_str());

    // Generates all windows
    for (unsigned int i = 0; i < numWindows; i++)
    {
        positionsWin[i] = glm::vec3
        (
            -15.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (15.0f - (-15.0f)))),
            1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0f - 1.0f))),
            -15.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (15.0f - (-15.0f))))
        );
        rotationsWin[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0f));
        orderDraw[i] = i;
    }


    double prevTime = 0.0;
    double deltaTime = 0.0;
    double currentTime = 0.0;

    unsigned int counter = 0;





    // Main while loop
    while (!glfwWindowShouldClose(window)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - prevTime;

        counter++;
        if (deltaTime > 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0f / deltaTime) * counter);
            std::string ms = std::to_string((deltaTime / counter) * 1000);
            std::string title = "Engine - " + FPS + "FPS / " + ms + "ms";
            glfwSetWindowTitle(window, title.c_str());
            prevTime = currentTime;
            counter = 0;

            // Handles camera inputs
            camera.Inputs(window);
        }


        // Specify the color of the background
        glClearColor(0.07f, 0.15f, 0.30f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Updates and exports the camera matrix to the Vertex Shader
        camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        // Draws model
        // Make it so the stencil test always passes
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // Enable modifying of the stencil buffer
        glStencilMask(0xFF);
        // Draw the normal model
        ground.Draw(shader_program, camera);

        glDisable(GL_CULL_FACE);
        grass.Draw(shader_grass_program, camera);
        glEnable(GL_BLEND);

        // Get distance from each window to the camera
        for (unsigned int i = 0; i < numWindows; i++)
        {
            distanceCamera[i] = glm::length(camera.position - positionsWin[i]);
        }
        // Sort windows by distance from camera
        qsort(orderDraw, numWindows, sizeof(unsigned int), compare);
        // Draw windows
        for (unsigned int i = 0; i < numWindows; i++)
        {
            windows.Draw(shader_window_program, camera, positionsWin[orderDraw[i]], glm::quat(1.0f, 0.0f, rotationsWin[orderDraw[i]], 0.0f));
        }

        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);

        // Make it so only the pixels without the value 1 pass the test
       glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //Disable modifying of the stencil buffer
       glStencilMask(0x00);
        // Disable the depth buffer
       glDisable(GL_DEPTH_TEST);


        // Second method from the tutorial
        outlining_shader_program.Activate();
        glUniform1f(glGetUniformLocation(outlining_shader_program.ID, "outlining"), 0.08f);
        ground.Draw(outlining_shader_program, camera);



        // Enable modifying of the stencil buffer
        glStencilMask(0xFF);
        // Clear stencil buffer
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        // Enable the depth buffer
        glEnable(GL_DEPTH_TEST);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the object we've created
    shader_program.Delete();
    shader_grass_program.Delete();
    outlining_shader_program.Delete();
    shader_window_program.Delete();
    // Destroy window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
}
