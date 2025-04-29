#include "../include/OpenGLScene.hpp"
#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLScene::OpenGLScene()
			: m_pOpenGLSceneImpl{ new OpenGLScene::OpenGLSceneImpl() }
		{
		}

		OpenGLScene::~OpenGLScene()
		{
			delete m_pOpenGLSceneImpl;
		}

		void OpenGLScene::AddObject(int id, IRenderableObjectOpenGL* object)
		{
			m_pOpenGLSceneImpl->AddObject(id, object);
		}

		void OpenGLScene::RemoveObject(int id)
		{
			m_pOpenGLSceneImpl->RemoveObject(id);
		}

		const std::unordered_map<int, IRenderableObjectOpenGL*> OpenGLScene::GetObjects() const
		{
			return m_pOpenGLSceneImpl->GetObjects();
		}
	}
}
