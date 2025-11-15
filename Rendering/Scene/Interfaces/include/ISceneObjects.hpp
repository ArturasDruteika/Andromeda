#ifndef ENVIRONMENT__I_SCENE_OBJECTS__HPP
#define ENVIRONMENT__I_SCENE_OBJECTS__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
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
		virtual void AddLuminousObject(int id, PhysicalProperties::LuminousBehavior* pLuminousObject) = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_OBJECTS__HPP