#include "../include/OpenGLScene.hpp"
#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Scene
	{
		OpenGLScene::OpenGLScene()
			: m_pOpenGLSceneImpl{ new OpenGLScene::OpenGLSceneImpl() }
		{
		}

		OpenGLScene::~OpenGLScene()
		{
			delete m_pOpenGLSceneImpl;
		}
	}
}
