#ifndef SPACE__SCENE__SCENE_OBJECTS__HPP
#define SPACE__SCENE__SCENE_OBJECTS__HPP


#include "../../Objects/include/GeometricObject.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneObjects.hpp"
#include <map>


namespace Andromeda::Space
{
	class SPACE_API SceneObjects
		: public virtual ISceneObjects
	{
	public:
		SceneObjects();
		~SceneObjects() override;

		// Getters
		const std::unordered_map<int, IGeometricObject*>& GetObjects() const override;
		
		virtual void AddObject(int id, IGeometricObject* object) override;
		virtual void RemoveObject(int id) override;

	protected:
		std::unordered_map<int, IGeometricObject*> m_objects;
	};
}


#endif // SPACE__SCENE__SCENE_OBJECTS__HPP