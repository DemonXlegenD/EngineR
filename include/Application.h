#pragma once

#include <string>


#include "Module/ModuleManager.h"

namespace Engine {

class Application
{

public: 

	Application() = default;
	~Application() = default;

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void Init();

	void Run() const;

	void Quit() { shouldQuit = true; }

	static Application* GetInstance();

private:
	static Application* instance;
	ModuleManager* moduleManager = new ModuleManager;
	bool shouldQuit = false;

	std::string path;
};

}


