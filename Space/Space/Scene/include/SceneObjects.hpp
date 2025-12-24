#ifndef SPACE__SCENE__SCENE_OBJECTS__HPP
#define SPACE__SCENE__SCENE_OBJECTS__HPP


#include "../../Objects/include/GeometricObject.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "Andromeda/Space/Scene/ISceneObjects.hpp"
#include <map>


namespace Andromeda::Space
{
	class SceneObjects
		: public virtual ISceneObjects
	{
	public:
		SceneObjects();
		~SceneObjects() override;

		// Getters
		const std::unordered_map<int, IGeometricObject*>& GetObjects() const override;
		
		void AddObject(int id, IGeometricObject* object) override;
		void RemoveObject(int id) override;
		void AddLightObject(int id, ILightObject* pLightObject) override;

	protected:
		std::unordered_map<int, IGeometricObject*> m_objects;
		std::unordered_map<int, ILightObject*> m_luminousObjects;
	};
}


#endif // SPACE__SCENE__SCENE_OBJECTS__HPP