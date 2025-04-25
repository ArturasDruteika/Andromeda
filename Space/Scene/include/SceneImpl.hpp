#ifndef SPACE__SCENE_IMPL__HPP
#define SPACE__SCENE_IMPL__HPP


#include "../include/Scene.hpp"


namespace Andromeda
{
	namespace Space
	{
		class Scene::SceneImpl
		{
		public:
			SceneImpl();
			~SceneImpl();

			SceneImpl(const SceneImpl& other) = delete;	// Prevent Copy Constructor
			SceneImpl& operator=(const SceneImpl& other) = delete;	// Prevent Copy Assignment
			SceneImpl(SceneImpl&& other) noexcept = delete;	// Prevent Move Constructor
			SceneImpl& operator=(SceneImpl&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(int id, ObjectBase* pObj);
			void RemoveObject(int id);

		private:
			std::unordered_map<int, ObjectBase*> m_objectsMap;
		};
	}
}


#endif // SPACE__SCENE_IMPL__HPP