#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Scene
	{
		OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
		{
		}

		OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl()
		{
		}

		void OpenGLScene::OpenGLSceneImpl::AddObject(OpenGLRenderableObject* object)
		{
		}

		void OpenGLScene::OpenGLSceneImpl::RemoveObject(OpenGLRenderableObject* object)
		{
		}

		const std::vector<OpenGLRenderableObject*> OpenGLScene::OpenGLSceneImpl::GetObjects() const
		{
			return m_renderableObjsPtrsVec;
		}
	}
}
