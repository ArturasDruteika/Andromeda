#include "../include/OpenGLScene.hpp"
#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Environment
	{
		OpenGLScene::OpenGLScene()
			: m_pOpenGLSceneImpl{ new OpenGLScene::OpenGLSceneImpl() }
		{
		}

		OpenGLScene::~OpenGLScene()
		{
			delete m_pOpenGLSceneImpl;
		}

		void OpenGLScene::AddObject(int id, OpenGLRenderableObject* object)
		{
			m_pOpenGLSceneImpl->AddObject(id, object);
		}

		void OpenGLScene::RemoveObject(int id)
		{
			m_pOpenGLSceneImpl->RemoveObject(id);
		}

		const std::unordered_map<int, OpenGLRenderableObject*> OpenGLScene::GetObjects() const
		{
			return m_pOpenGLSceneImpl->GetObjects();
		}
	}
}
