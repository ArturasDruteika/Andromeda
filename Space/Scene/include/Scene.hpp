#ifndef SPACE__SCENE__HPP
#define SPACE__SCENE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../Objects/include/ObjectBase.hpp"


namespace Andromeda
{
	namespace Space
	{
		class SPACE_API Scene
		{
		public:
			Scene();
			~Scene();

			Scene(const Scene& other) = delete;	// Prevent Copy Constructor
			Scene& operator=(const Scene& other) = delete;	// Prevent Copy Assignment
			Scene(Scene&& other) noexcept = delete;	// Prevent Move Constructor
			Scene& operator=(Scene&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(int id, ObjectBase* pObj);
			void RemoveObject(int id);

		private:
			class SceneImpl;
			SceneImpl* m_pSceneImpl;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP