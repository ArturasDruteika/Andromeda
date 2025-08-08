#ifndef ENVIRONMENT__I_SCENE_LIGHTING__HPP
#define ENVIRONMENT__I_SCENE_LIGHTING__HPP


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
#include "../../../Light/LightTypes/include/DirectionalLight.hpp"
#include "../../../Light/LightTypes/include/PointLight.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ISceneLighting
    {
    public:
        virtual ~ISceneLighting();

        // Getters
        virtual const std::unordered_map<int, const DirectionalLight*> GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const PointLight*> GetPointLights() const = 0;
        virtual const std::unordered_map<int, LuminousBehavior*>& GetLuminousObjects() const = 0;
    };
}


#endif // ENVIRONMENT__I_SCENE_LIGHTING__HPP