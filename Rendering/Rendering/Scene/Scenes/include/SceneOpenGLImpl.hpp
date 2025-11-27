#ifndef RENDERING__SCENE_IMPL__HPP
#define RENDERING__SCENE_IMPL__HPP


#include "../include/SceneOpenGL.hpp"
#include "../../Abstracts/include/Scene.hpp"


namespace Andromeda::Rendering
{
	class SceneOpenGL::SceneOpenGLImpl
		: public Scene
	{
	public:
		SceneOpenGLImpl();
		~SceneOpenGLImpl();

		SceneOpenGLImpl(const SceneOpenGLImpl& other) = delete;	// Prevent Copy Constructor
		SceneOpenGLImpl& operator=(const SceneOpenGLImpl& other) = delete;	// Prevent Copy Assignment
		SceneOpenGLImpl(SceneOpenGLImpl&& other) noexcept = delete;	// Prevent Move Constructor
		SceneOpenGLImpl& operator=(SceneOpenGLImpl&& other) noexcept = delete;	// Prevent Move Assignment
	};
}


#endif // RENDERING__RENDERING__HPP