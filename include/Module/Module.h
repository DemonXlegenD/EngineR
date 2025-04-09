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
		 * @brief Destructeur prot�g�.
		 *
		 * Le destructeur est prot�g� car les modules doivent �tre d�truits uniquement par le ModuleManager.
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
		 * @brief D�marre le module.
		 */
		virtual void Start()
		{
			Debug::Log("Start " + name, Debug::LogType::LOADING);
		}

		/**
		 * @brief Effectue une mise � jour fixe du module.
		 */
		virtual void FixedUpdate()
		{
		}

		/**
		 * @brief Met � jour le module.
		 */
		virtual void Update()
		{
		}

		/**
		 * @brief Fonction pr�-rendu du module.
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
		 * @brief Lib�re les ressources utilis�es par le module.
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