#ifndef ENGINECORE__APPLICATION__HPP
#define ENGINECORE__APPLICATION__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "IRenderableObjectOpenGL.hpp"
#include "DirectionalLight.hpp"


namespace Andromeda::EngineCore
{
	class ENGINECORE_API Application
	{
	public:
		Application();
		~Application();

		Application(const Application& other) = delete;	// Prevent Copy Constructor
		Application& operator=(const Application& other) = delete;	// Prevent Copy assignment
		Application(Application&& other) noexcept = delete;	// Prevent Move constructor
		Application& operator=(const Application&& other) noexcept = delete;	//Prevent Move assignment

		void Init();
		void RunMainLoop();
		void DeInit();
		void AddToScene(int id, Rendering::IRenderableObjectOpenGL* object);
		void AddToScene(int id, Rendering::LuminousBehavior* object);
		void RemoveFromScene(int id);

	private:
		class ApplicationImpl;
		ApplicationImpl* m_pApplicationImpl;
	};
}


#endif // ENGINECORE__APPLICATION__HPP