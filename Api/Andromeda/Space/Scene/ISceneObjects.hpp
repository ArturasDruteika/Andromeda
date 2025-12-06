#ifndef API__SCENE__I_SCENE_OBJECTS__HPP
#define API__SCENE__I_SCENE_OBJECTS__HPP


#include "../Objects/IGeometricObject.hpp"
#include <map>


namespace Andromeda
{
	class ISceneObjects
	{
	public:
		virtual ~ISceneObjects() = default;

		// Getters
		virtual const std::unordered_map<int, IGeometricObject*>& GetObjects() const = 0;
		
		virtual void AddObject(int id, IGeometricObject* object) = 0;
		virtual void RemoveObject(int id) = 0;
		virtual void AddLuminousObject(int id, Space::LuminousBehavior* pLuminousObject) = 0;
	};
}


#endif // API__SCENE__I_SCENE_OBJECTS__HPP