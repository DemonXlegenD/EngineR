#pragma once

#include <glad/glad.h>
#include "API_Graphique/ISwapchain.h"

#include "Debug.h"

namespace Engine {

    class OpenGLSwapchain : public Interface::ISwapchain
    {
    public:
        void Create(Interface::IDevice* device) override {
            Debug::Log("OpenGL Swapchain Created.", Debug::LogType::LOADING);

            OpenGLDevice* glDevice = device->CastOpenGL();
            if (!glDevice) {
                Debug::Log("Failed to cast to OpenGLDevice!", Debug::LogType::ERROR);
                return;
            }  
            Debug::Log("OpenGL Swapchain Created.", Debug::LogType::SUCCESS);
        }

        void Destroy() override {
            Debug::Log("OpenGL Swapchain Destroyed.", Debug::LogType::SUCCESS);
        }

        void Present() override {
            glfwSwapBuffers(windowModule->GetWindow());
        }

        void Resize(int width, int height) override {
            glViewport(0, 0, width, height);
        }

    };


}