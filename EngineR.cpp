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

float rectangleVertices[] =
{
    // Coords    // texCoords
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,

     1.0f,  1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f
};

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
    Shader framebuffer_program("framebuffer.vert", "framebuffer.frag");

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

    framebuffer_program.Activate();
    glUniform1i(glGetUniformLocation(framebuffer_program.ID, "screenTexture"), 0);

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

    Model grass((resources_path + "Models/crow/scene.gltf").c_str());
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

    // Prepare framebuffer rectangle VBO and VAO
    unsigned int rectVAO, rectVBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    double prevTime = 0.0;
    double deltaTime = 0.0;
    double currentTime = 0.0;

    unsigned int counter = 0;

    // Create Frame Buffer Object
    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Create Framebuffer Texture
    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    // Create Render Buffer Object
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


    // Error checking framebuffer
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer error: " << fboStatus << std::endl;



    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        // Specify the color of the background
        glClearColor(0.07f, 0.15f, 0.30f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
       
        glEnable(GL_DEPTH_TEST);

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

        // Bind the default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // Draw the framebuffer rectangle
        framebuffer_program.Activate();
        glBindVertexArray(rectVAO);
        glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
    glDeleteFramebuffers(1, &FBO);
    shader_program.Delete();
    shader_grass_program.Delete();
    outlining_shader_program.Delete();
    shader_window_program.Delete();


    // Destroy window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
}
