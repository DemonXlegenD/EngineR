#pragma once

#include "Debug.h"

namespace Engine {
	class OpenGLDevice;

	namespace Interface {

		class IDevice
		{
		public:
			virtual ~IDevice() = default;
			virtual void Create() = 0;
			virtual void Destroy() = 0;

			/*virtual VulkanDevice* CastVulkan() { Debug::Log("Try to return wrong cast type!", Debug::LogType::ERROR); return nullptr; };*/
			virtual OpenGLDevice* CastOpenGL();
		};
	}
}