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

		float OpenGLScene::GetAmbientStrength() const
		{
			return m_pOpenGLSceneImpl->GetAmbientStrength();
		}

		const std::unordered_map<int, IRenderableObjectOpenGL*>& OpenGLScene::GetObjects() const
		{
			return m_pOpenGLSceneImpl->GetObjects();
		}

		const std::unordered_map<int, IRenderableObjectOpenGL*>& OpenGLScene::GetLuminousObjects() const
		{
			return m_pOpenGLSceneImpl->GetLuminousObjects();
		}

		void OpenGLScene::SetAmbientStrength(float ambientStrength)
		{
			m_pOpenGLSceneImpl->SetAmbientStrength(ambientStrength);
		}

		void OpenGLScene::AddObject(int id, IRenderableObjectOpenGL* object)
		{
			m_pOpenGLSceneImpl->AddObject(id, object);
		}

		void OpenGLScene::RemoveObject(int id)
		{
			m_pOpenGLSceneImpl->RemoveObject(id);
		}

		void OpenGLScene::ResizeGrid(float resizeFactor)
		{
			m_pOpenGLSceneImpl->ResizeGrid(resizeFactor);
		}
	}
}
