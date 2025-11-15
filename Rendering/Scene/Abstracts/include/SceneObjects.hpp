#ifndef ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP


#include "pch.hpp"
#include "SceneLighting.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class SceneObjects
		: public SceneLighting
	{
	public:
		SceneObjects();
		~SceneObjects();

		// Getters
		const std::unordered_map<int, IRenderableObject*>& GetObjects() const;
		
		void AddObject(int id, IRenderableObject* object);
		void RemoveObject(int id);
		void AddLuminousObject(int id, PhysicalProperties::LuminousBehavior* pLuminousObject);

	protected:
		std::unordered_map<int, IRenderableObject*> m_objects;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP