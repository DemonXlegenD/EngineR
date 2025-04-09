#pragma once

#include <string>

#include "Debug.h"

namespace Engine {

	class ModuleManager;

	class Module
	{
	friend class ModuleManager;

	protected:
		static uint32_t id;
		std::string name;
		ModuleManager* moduleManager = nullptr;

		Module() {
			id++;
		}

		/**
		 * @brief Destructeur protégé.
		 *
		 * Le destructeur est protégé car les modules doivent être détruits uniquement par le ModuleManager.
		 */
		~Module() = default;


	public:

#pragma region Life Cycle

		/**
		* @brief Initialise le module.
		*/
		virtual void Init()
		{
			if(name.empty()) 
			{
				Debug::Log("Name is empty, please add a name!", Debug::LogType::WARNING);
				name = "Module" + id;
				Debug::Log("Default name assigned : " + name , Debug::LogType::MESSAGE);
			}
			Debug::Log("Init " + name, Debug::LogType::LOADING);
		}

		/**
		 * @brief Démarre le module.
		 */
		virtual void Start()
		{
			Debug::Log("Start " + name, Debug::LogType::LOADING);
		}

		/**
		 * @brief Effectue une mise à jour fixe du module.
		 */
		virtual void FixedUpdate()
		{
		}

		/**
		 * @brief Met à jour le module.
		 */
		virtual void Update()
		{
		}

		/**
		 * @brief Fonction pré-rendu du module.
		 */
		virtual void PreRender()
		{
		}

		/**
		 * @brief Rendu du module.
		 */
		virtual void Render()
		{
		}

		/**
		 * @brief Rendu de l'interface graphique du module.
		 */
		virtual void RenderGui()
		{
		}

		/**
		 * @brief Fonction post-rendu du module.
		 */
		virtual void PostRender()
		{
		}

		/**
		 * @brief Libère les ressources utilisées par le module.
		 */
		virtual void Release()
		{
			Debug::Log("Release " + name, Debug::LogType::LOADING);
		}

		/**
		 * @brief Finalise le module.
		 */
		virtual void Finalize()
		{
			Debug::Log("Finalize " + name, Debug::LogType::LOADING);
		}

#pragma endregion

	};

}