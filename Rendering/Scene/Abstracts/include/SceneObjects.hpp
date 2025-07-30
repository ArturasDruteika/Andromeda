#ifndef ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP


#include "pch.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class SceneObjects
	{
	public:
		SceneObjects();
		~SceneObjects();

		// Getters
		const std::unordered_map<int, IRenderableObject*>& GetObjects() const;
		
		void AddObject(int id, IRenderableObject* object);
		void RemoveObject(int id);

	protected:
		std::unordered_map<int, IRenderableObject*> m_objects;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_OBJECTS__HPP