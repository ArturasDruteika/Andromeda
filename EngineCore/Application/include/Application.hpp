#ifndef ENGINECORE__APPLICATION__HPP
#define ENGINECORE__APPLICATION__HPP


#if defined(_WIN32)
	#if defined(ENGINECORE_EXPORT)
		#define ENGINECORE_API __declspec(dllexport)
	#else
		#define ENGINECORE_API __declspec(dllimport)
	#endif /* ENGINECORE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define ENGINECORE_API __attribute__((visibility("default")))
#endif


#include "IRenderableObjectOpenGL.hpp"
#include "DirectionalLight.hpp"


namespace Andromeda
{
	namespace EngineCore
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
			void AddToScene(int id, Rendering::DirectionalLight* object);
			void RemoveFromScene(int id);

		private:
			class ApplicationImpl;
			ApplicationImpl* m_pApplicationImpl;
		};
	}
}


#endif // ENGINECORE__APPLICATION__HPP