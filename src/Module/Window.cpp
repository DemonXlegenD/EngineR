#include "Module/Window.h"

#include "Debug.h"  

#include "Application.h"


namespace Engine {

	void Window::Init() {
        Module::Init();

        // Initialize GLFW
        if (!glfwInit())
        {
            Debug::Log("Erreur lors de l'initialisation de GLFW", Debug::LogType::ERROR);
            exit(EXIT_FAILURE);
        }

        // Tell GLFW what version of OpenGL we are using
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Windows Hint
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        // Tell GLFW we are using the CORE profile (modern functions)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFWwindow object 
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle.c_str(), nullptr, nullptr);

        if (window == nullptr) {
            Debug::Log("Erreur lors de la création de la fenêtre GLFW", Debug::LogType::ERROR);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowUserPointer(window, this);
        // Introduce the window into the current context
        glfwMakeContextCurrent(window);
	}

    void Window::Start()
    {
        Module::Start();
    }

    void Window::FixedUpdate()
    {
        Module::FixedUpdate();
    }

    void Window::Update()
    {
        Module::Update();

        if (!ShouldClose())
        {

            glfwSwapBuffers(window);
            glfwPollEvents();
            
        }
        else
        {
            /*moduleManager->GetModule<RHIModule>()->GetDevice()->Device().waitIdle();*/
            Application::GetInstance()->Quit();
        }
    }

    void Window::PreRender()
    {
        Module::PreRender();
    }

    void Window::Render()
    {
        Module::Render();
    }

    void Window::RenderGui()
    {
        Module::RenderGui();
    }

    void Window::PostRender()
    {
        Module::PostRender();
    }

    void Window::Release()
    {
        Module::Release();
    }

    void Window::Finalize()
    {
        Module::Finalize();

        // Destroy window before ending the program
        glfwDestroyWindow(window);

        // Terminate GLFW before ending the program
        glfwTerminate();
    }
}