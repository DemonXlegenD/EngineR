#include "Module/Time.h"

namespace Engine {

	float Time::deltaTime = 0.0f;

	void Time::Init()
	{
		Module::Init();
		currentTime = std::chrono::high_resolution_clock::now();
		beginTime = std::chrono::high_resolution_clock::now();
		deltaTime = 0.0f;
	}

	void Time::Start()
	{
		Module::Start();
	}

	void Time::FixedUpdate()
	{
		Module::FixedUpdate();
	}

	void Time::Update()
	{
		Module::Update();
		const auto current_time = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> duration = current_time - currentTime;

		deltaTime = duration.count();
		currentTime = current_time;

	}

	void Time::PreRender()
	{
		Module::PreRender();
	}

	void Time::Render()
	{
		Module::Render();
	}

	void Time::RenderGui()
	{
		Module::RenderGui();
	}

	void Time::PostRender()
	{
		Module::PostRender();
	}

	void Time::Release()
	{
		Module::Release();
	}

	void Time::Finalize()
	{
		Module::Finalize();
	}
}