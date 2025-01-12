	#ifndef SCENE__SCENE_IMPL__HPP
	#define SCENE__SCENE_IMPL__HPP


	#include "../include/OpenGLScene.hpp"


	namespace Andromeda
	{
		namespace Scene
		{
			class OpenGLScene::OpenGLSceneImpl
			{
			public:
				OpenGLSceneImpl();
				~OpenGLSceneImpl();

				OpenGLSceneImpl(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Constructor
				OpenGLSceneImpl& operator=(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Assignment
				OpenGLSceneImpl(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Constructor
				OpenGLSceneImpl& operator=(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Assignment

			private:
			};
		}
	}


	#endif // SCENE__SCENE_IMPL__HPP