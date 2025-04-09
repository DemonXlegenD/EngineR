#include "Module/RHI.h"
#include "Module/ModuleManager.h"
#include "API_Graphique/OpenGL/OpenGLRenderInterface.h"

namespace Engine {


	void RHI::Init()
	{
		Module::Init();
		renderInterface = new OpenGLRenderInterface();
		device = renderInterface->InstantiateDevice();
		device->Create();

		swapchain = renderInterface->InstantiateSwapchain();
		swapchain->SetWindowModule(moduleManager->GetModule<Window>());
		swapchain->Create(device);
	}

	void RHI::Start()
	{
		Module::Start();
	}

	void RHI::FixedUpdate()
	{
		Module::FixedUpdate();
	}

	void RHI::Update()
	{
		Module::Update();

	}

	void RHI::PreRender()
	{
		Module::PreRender();
	}

	void RHI::Render()
	{
		Module::Render();
	}

	void RHI::RenderGui()
	{
		Module::RenderGui();
	}

	void RHI::PostRender()
	{
		Module::PostRender();
	}

	void RHI::Release()
	{
		Module::Release();
	}

	void RHI::Finalize()
	{
		Module::Finalize();

		renderInterface->DeleteDevice(device);
		renderInterface->DeleteSwapchain(swapchain);
	}
}