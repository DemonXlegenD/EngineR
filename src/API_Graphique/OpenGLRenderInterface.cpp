#include "API_Graphique/OpenGL/OpenGLRenderInterface.h"

#include "API_Graphique/OpenGL/OpenGLDevice.h"
#include "API_Graphique/OpenGL/OpenGLSwapchain.h"

namespace Engine {
	Interface::IDevice* OpenGLRenderInterface::InstantiateDevice() { return new OpenGLDevice(); }
	Interface::ISwapchain* OpenGLRenderInterface::InstantiateSwapchain() { return new OpenGLSwapchain(); }
}