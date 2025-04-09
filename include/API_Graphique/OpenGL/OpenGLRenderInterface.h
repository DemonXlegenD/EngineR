#pragma once

#include "Module/RHI.h"

#include "API_Graphique/IRenderInterface.h"

namespace Engine {

	class OpenGLRenderInterface : public Interface::IRenderInterface
	{
	public:
		Interface::IDevice* InstantiateDevice() override;
		Interface::ISwapchain* InstantiateSwapchain() override;
	};

}