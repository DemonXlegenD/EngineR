#pragma once

#include "Module/Window.h"
#include "IDevice.h"

namespace Engine {
	namespace Interface {
		class ISwapchain
		{
		protected:
			Window* windowModule;

		public:
			virtual ~ISwapchain() = default;
			virtual void Create(IDevice* _device) = 0;
			virtual void Destroy() = 0;
			virtual void Present() = 0;
			virtual void Resize(int _width, int _height) = 0;

			void SetWindowModule(Window* _module) { windowModule = _module; }
		};
	}
}