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

#include "Debug.h"

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

float skyboxVertices[] =
{
    //   Coordinates
    -1.0f, -1.0f,  1.0f,//        7--------6
     1.0f, -1.0f,  1.0f,//       /|       /|
     1.0f, -1.0f, -1.0f,//      4--------5 |
    -1.0f, -1.0f, -1.0f,//      | |      | |
    -1.0f,  1.0f,  1.0f,//      | 3------|-2
     1.0f,  1.0f,  1.0f,//      |/       |/
     1.0f,  1.0f, -1.0f,//      0--------1
    -1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
    // Right
    1, 2, 6,
    6, 5, 1,
    // Left
    0, 4, 7,
    7, 3, 0,
    // Top
    4, 5, 6,
    6, 7, 4,
    // Bottom
    0, 3, 2,
    2, 1, 0,
    // Back
    0, 1, 5,
    5, 4, 0,
    // Front
    3, 7, 6,
    6, 2, 3
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

    std::string shader_path = directory_path + "/Shaders/";

    // Generates Shader object using shaders default.vert and default.frag
    Engine::Shader shader_program; shader_program.Load((shader_path + "default.vert").c_str(), (shader_path + "default.frag").c_str());
    Engine::Shader shader_grass_program; shader_grass_program.Load((shader_path + "default.vert").c_str(), (shader_path + "grass.frag").c_str());
    Engine::Shader shader_window_program; shader_window_program.Load((shader_path + "default.vert").c_str(), (shader_path + "window.frag").c_str());
    Engine::Shader framebuffer_program; framebuffer_program.Load((shader_path + "framebuffer.vert").c_str(), (shader_path + "framebuffer.frag").c_str());

    Engine::Shader outlining_shader_program; outlining_shader_program.Load((shader_path + "outlining.vert").c_str(), (shader_path + "outlining.frag").c_str());

    Engine::Shader skyboxShader; skyboxShader.Load((shader_path + "skybox.vert").c_str(), (shader_path + "skybox.frag").c_str());

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shader_program.Activate();
    glUniform4f(glGetUniformLocation(shader_program.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_program.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    shader_grass_program.Activate();
    glUniform4f(glGetUniformLocation(shader_grass_program.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_grass_program.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    shader_window_program.Activate();
    glUniform4f(glGetUniformLocation(shader_window_program.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader_window_program.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    framebuffer_program.Activate();
    glUniform1i(glGetUniformLocation(framebuffer_program.GetID(), "screenTexture"), 0);

    skyboxShader.Activate();
    glUniform1i(glGetUniformLocation(skyboxShader.GetID(), "skybox"), 0);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    Engine::Camera camera(width, height, glm::vec3(0.f, 0.f, 0.f));

    Engine::Model grass((resources_path + "Models/crow/scene.gltf").c_str());
    Engine::Model ground((resources_path + "Models/ground/scene.gltf").c_str());
    Engine::Model windows((resources_path + "Models/window/scene.gltf").c_str());

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



    // Create VAO, VBO, and EBO for the skybox
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string facesCubemap[6] = {
        resources_path + "Cubemaps/skybox/right.jpg",
              resources_path + "Cubemaps/skybox/left.jpg",
                    resources_path + "Cubemaps/skybox/top.jpg",
                          resources_path + "Cubemaps/skybox/bottom.jpg",
                                resources_path + "Cubemaps/skybox/front.jpg",
                                      resources_path + "Cubemaps/skybox/back.jpg",
    };

    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < 6; i++)
    {
        Engine::Debug::Log(facesCubemap[i]);
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }

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

        }
            camera.Inputs(window);
      
        // Specify the color of the background
        glClearColor(1.f, 1.f, 1.f, 1.0f);  
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Updates and exports the camera matrix to the Vertex Shader
        camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        ground.Draw(shader_program, camera);

        glDepthFunc(GL_LEQUAL);

        skyboxShader.Activate();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        view = glm::mat4(glm::mat3(glm::lookAt(camera.position, camera.position + camera.orientation, camera.up)));
        proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS);


        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the object we've created
    shader_program.Unload();
    shader_grass_program.Unload();
    outlining_shader_program.Unload();
    shader_window_program.Unload();


    // Destroy window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
}
