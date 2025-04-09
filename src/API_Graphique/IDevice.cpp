#include "API_Graphique/IDevice.h"

#include "API_Graphique/OpenGL/OpenGLDevice.h"

namespace Engine {
	namespace Interface {
		OpenGLDevice* IDevice::CastOpenGL() { Debug::Log("Try to return wrong cast type!", Debug::LogType::ERROR); return nullptr; }
	}
}