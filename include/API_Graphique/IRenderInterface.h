#pragma once

#include "IDevice.h"
#include "ISwapchain.h"

namespace Engine {
	namespace Interface {
		class IRenderInterface
		{
		public:
			virtual IDevice* InstantiateDevice() = 0;
			virtual ISwapchain* InstantiateSwapchain() = 0;
			virtual void DeleteDevice(IDevice* _device) { delete _device; }
			virtual void DeleteSwapchain(ISwapchain* _swapchain) { delete _swapchain; }
		};
	}
}