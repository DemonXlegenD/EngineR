#pragma once

#include <chrono>

#include "Module.h"

namespace Engine {

class Time : public Module
{
public:
	Time() : Module() {
		name = "Time Module";
	}

#pragma region Life Cycle

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

	static float deltaTime;

private:
	std::chrono::high_resolution_clock::time_point beginTime;
	std::chrono::high_resolution_clock::time_point currentTime;
};

}


