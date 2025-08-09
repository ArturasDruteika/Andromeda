#ifndef ENVIRONMENT__I_SCENE_OBJECTS__HPP
#define ENVIRONMENT__I_SCENE_OBJECTS__HPP


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
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API ISceneObjects
	{
	public:
		virtual ~ISceneObjects();

		// Getters
		virtual const std::unordered_map<int, IRenderableObject*>& GetObjects() const = 0;
		
		virtual void AddObject(int id, IRenderableObject* object) = 0;
		virtual void RemoveObject(int id) = 0;
		virtual void AddDirectionaLight(int id, DirectionalLight* pDirectionalLight) = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_OBJECTS__HPP