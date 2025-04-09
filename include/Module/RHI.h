#pragma once
#include <iostream>
#include <glad/glad.h>

#include "Module.h"
#include "Debug.h"
#include "API_Graphique/OpenGL/OpenGLRenderInterface.h"

#include "Window.h"

#include "API_Graphique/IDevice.h"
#include "API_Graphique/ISwapchain.h"
#include "API_Graphique/IRenderInterface.h"

namespace Engine {

	class RHI : public Module {
#pragma region Life Cycle
	public:
		/**
		 * @brief Initialise le module.
		 */
		void Init() override;

		/**
		 * @brief D�marre le module.
		 */
		void Start() override;

		/**
		 * @brief Effectue une mise � jour fixe du module.
		 */
		void FixedUpdate() override;

		/**
		 * @brief Met � jour le temps �coul� depuis la derni�re frame.
		 */
		void Update() override;

		/**
		 * @brief Fonction pr�-rendu du module.
		 */
		void PreRender() override;

		/**
		 * @brief Rendu du module.
		 */
		void Render() override;

		/**
		 * @brief Rendu de l'interface graphique du module.
		 */
		void RenderGui() override;

		/**
		 * @brief Fonction post-rendu du module.
		 */
		void PostRender() override;

		/**
		 * @brief Lib�re les ressources utilis�es par le module.
		 */
		void Release() override;

		/**
		 * @brief Finalise le module.
		 */
		void Finalize() override;

#pragma endregion

	private:
		Interface::IRenderInterface* renderInterface;
		Interface::IDevice* device;
		Interface::ISwapchain* swapchain;


	};
}

