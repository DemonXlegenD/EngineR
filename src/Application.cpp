#include "Application.h"

#include <filesystem>
#include "Debug.h"

namespace Engine {

	Application* Application::instance = nullptr;

	Application* Application::GetInstance()
	{
		if (instance == nullptr) instance = new Application();

		return instance;
	}

	void Application::Init()
	{
		Debug::Log("Init Application", Debug::LogType::LOADING);

		path = std::filesystem::current_path().string();
		Debug::Log("Path : " + path, Debug::LogType::MESSAGE);

		moduleManager->CreateDefaultModules();
		moduleManager->Init();

		Debug::Log("Init Application", Debug::LogType::SUCCESS);
	}

	void Application::Run() const
	{
		moduleManager->Start();

		while (!shouldQuit)
		{
			moduleManager->Update();
			moduleManager->PreRender();
			moduleManager->Render();
			moduleManager->RenderGui();
			moduleManager->PostRender();
		}

		moduleManager->Release();
		moduleManager->Finalize();
	}

}