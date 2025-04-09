#pragma once
#include "Module.h"

#include <GLFW/glfw3.h>
#include <string>

namespace Engine {

class Window : public Module
{
public:
	static constexpr int WIDTH = 800; ///< Largeur de la fenétre par défaut.
	static constexpr int HEIGHT = 600; ///< Hauteur de la fenétre par défaut.

	Window() : Module() {
		name = "Window Module";
		window = nullptr;
		windowTitle = "Engine";
	}

	inline GLFWwindow* GetWindow() const { return window; }

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

private:
	GLFWwindow* window;
	std::string windowTitle;
	std::string windowInformationTitle;

	inline bool ShouldClose() const { return glfwWindowShouldClose(window); }

	inline std::string GetTitle() { return windowTitle + " - " + windowInformationTitle; }
};

}



