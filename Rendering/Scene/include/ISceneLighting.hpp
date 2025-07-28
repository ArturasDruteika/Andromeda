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
#include "../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ISceneLighting
    {
    public:
        virtual ~ISceneLighting();

        // Getters
        virtual const std::unordered_map<int, IRenderableObject*>& GetLuminousObjects() const = 0;

        virtual void AddDirectionalLight(
            int id,
            const Math::Vec3& direction,
            const Math::Vec3& color = Math::Vec3(1.0f, 1.0f, 1.0f),
            float intensity = 1.0f,
            const Math::Vec3& ambient = Math::Vec3(0.1f, 0.1f, 0.1f),
            const Math::Vec3& diffuse = Math::Vec3(0.4f, 0.4f, 0.4f),
            const Math::Vec3& specular = Math::Vec3(0.4f, 0.4f, 0.4f)
        ) = 0;
        virtual void RemoveDirectionalLight(int id) = 0;
    };
}


#endif // ENVIRONMENT__I_SCENE_LIGHTING__HPP