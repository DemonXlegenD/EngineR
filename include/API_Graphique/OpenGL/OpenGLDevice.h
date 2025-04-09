#pragma once
#include <glad/glad.h>

#include "Debug.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Module/RHI.h"

#include "API_GRAPHIQUE/IDevice.h"

namespace Engine {

    class OpenGLDevice : public Interface::IDevice

    {
    private:
        VertexArray VAO;
        VertexBuffer VBO;


    public:
        OpenGLDevice() = default;

        void Create() override {
            Debug::Log("Creating OpenGL Device.", Debug::LogType::LOADING);
            gladLoadGL();

            VAO.Create();
            VBO.Create();


            Debug::Log("OpenGL Device Created.", Debug::LogType::SUCCESS);
        }

        void Destroy() override {
            Debug::Log("Destroying OpenGL Device.", Debug::LogType::LOADING);
            // Cleanup OpenGL context
            Debug::Log("OpenGL Device Destroyed.", Debug::LogType::SUCCESS);
        }

        OpenGLDevice* CastOpenGL() override { return this; }
    };
}