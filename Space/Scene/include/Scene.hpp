#ifndef SPACE__SCENE__HPP
#define SPACE__SCENE__HPP


#if defined(_WIN32)
	#if defined(SPACE_EXPORT)
		#define SPACE_API __declspec(dllexport)
	#else
		#define SPACE_API __declspec(dllimport)
	#endif /* SPACE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define SPACE_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "../../Objects/include/ObjectBase.hpp"


namespace Andromeda
{
	namespace Space
	{
		class SPACE_API Scene
		{
		public:
			Scene();
			~Scene();

			Scene(const Scene& other) = delete;	// Prevent Copy Constructor
			Scene& operator=(const Scene& other) = delete;	// Prevent Copy Assignment
			Scene(Scene&& other) noexcept = delete;	// Prevent Move Constructor
			Scene& operator=(Scene&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(const ObjectBase& objBase);

		private:
			class SceneImpl;
			SceneImpl* m_pSceneImpl;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP