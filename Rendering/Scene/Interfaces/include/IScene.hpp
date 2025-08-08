#ifndef ENVIRONMENT__I_SCENE__HPP
#define ENVIRONMENT__I_SCENE__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "ISceneObjects.hpp"
#include "ISceneLighting.hpp"
#include "ISceneEnvironment.hpp"
#include "ISceneState.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API IScene :
        public ISceneObjects,
        public ISceneLighting,
        public ISceneEnvironment,
        public ISceneState
    {
    public:
        virtual ~IScene();

		// Getters
        virtual glm::vec3 GetSceneCenter() const = 0;
    };
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP