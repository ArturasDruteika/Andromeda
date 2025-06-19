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

		const std::unordered_map<int, IRenderableObjectOpenGL*> OpenGLScene::GetObjects() const
		{
			return m_pOpenGLSceneImpl->GetObjects();
		}

		const std::unordered_map<int, Math::Vec3> OpenGLScene::GetLightEmittingObjectsCoords() const
		{
			return m_pOpenGLSceneImpl->GetLightEmittingObjectsCoords();
		}

		const std::unordered_map<int, Math::Vec4> OpenGLScene::GetLightEmittingObjectsColors() const
		{
			return m_pOpenGLSceneImpl->GetLightEmittingObjectsColors();
		}

		const std::unordered_map<int, LuminousBehavior*> OpenGLScene::GetLuminousObjectsBehaviors() const
		{
			return m_pOpenGLSceneImpl->GetLuminousObjectsBehaviors();
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
