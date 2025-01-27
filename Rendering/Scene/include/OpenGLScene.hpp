#ifndef ENVIRONMENT__SCENE__HPP
#define ENVIRONMENT__SCENE__HPP


#include "pch.hpp"
#include "../../RenderableObjects/include/OpenGLRenderableObject.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLScene
		{
		public:
			OpenGLScene();
			~OpenGLScene();

			OpenGLScene(const OpenGLScene& other) = delete;	// Prevent Copy Constructor
			OpenGLScene& operator=(const OpenGLScene& other) = delete;	// Prevent Copy Assignment
			OpenGLScene(OpenGLScene&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLScene& operator=(OpenGLScene&& other) noexcept = delete;	// Prevent Move Assignment

			void AddObject(int id, OpenGLRenderableObject* object);
			void RemoveObject(int id);
			const std::unordered_map<int, OpenGLRenderableObject*> GetObjects() const;

		private:
			std::unordered_map<int, OpenGLRenderableObject*> m_renderableObjsPtrsMap;
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP