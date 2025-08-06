#ifndef RENDERING__SCENE_IMPL__HPP
#define RENDERING__SCENE_IMPL__HPP


#include "../include/OpenGLScene.hpp"
#include "../../Abstracts/include/Scene.hpp"


namespace Andromeda::Rendering
{
	class OpenGLScene::OpenGLSceneImpl
		: public Scene
	{
	public:
		OpenGLSceneImpl();
		~OpenGLSceneImpl();

		OpenGLSceneImpl(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Constructor
		OpenGLSceneImpl& operator=(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Assignment
		OpenGLSceneImpl(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLSceneImpl& operator=(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Assignment
	};
}


#endif // RENDERING__RENDERING__HPP