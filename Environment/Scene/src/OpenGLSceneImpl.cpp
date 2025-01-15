#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda
{
	namespace Environment
	{
		OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
		{
		}

		OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl()
		{
		}

		void OpenGLScene::OpenGLSceneImpl::AddObject(OpenGLRenderableObject* object)
		{
			m_renderableObjsPtrsVec.push_back(object);
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
