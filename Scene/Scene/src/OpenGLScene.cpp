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

		void OpenGLScene::AddObject(OpenGLRenderableObject* object)
		{
			m_pOpenGLSceneImpl->AddObject(object);
		}

		void OpenGLScene::RemoveObject(OpenGLRenderableObject* object)
		{
			m_pOpenGLSceneImpl->RemoveObject(object);
		}

		const std::vector<OpenGLRenderableObject*> OpenGLScene::GetObjects() const
		{
			return m_pOpenGLSceneImpl->GetObjects();
		}
	}
}
