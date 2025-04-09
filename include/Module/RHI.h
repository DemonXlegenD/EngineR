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
		 * @brief Démarre le module.
		 */
		void Start() override;

		/**
		 * @brief Effectue une mise à jour fixe du module.
		 */
		void FixedUpdate() override;

		/**
		 * @brief Met à jour le temps écoulé depuis la dernière frame.
		 */
		void Update() override;

		/**
		 * @brief Fonction pré-rendu du module.
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
		 * @brief Libère les ressources utilisées par le module.
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

