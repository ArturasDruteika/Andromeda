#ifndef API__SCENE__I_SCENE_OBJECTS__HPP
#define API__SCENE__I_SCENE_OBJECTS__HPP


#include "../Objects/IRenderableObject.hpp"
#include <map>


namespace Andromeda
{
	class ISceneObjects
	{
	public:
		virtual ~ISceneObjects() = default;

		// Getters
		virtual const std::unordered_map<int, IRenderableObject*>& GetObjects() const = 0;
		
		virtual void AddObject(int id, IRenderableObject* object) = 0;
		virtual void RemoveObject(int id) = 0;
		virtual void AddLuminousObject(int id, PhysicalProperties::LuminousBehavior* pLuminousObject) = 0;
	};
}


#endif // API__SCENE__I_SCENE_OBJECTS__HPP