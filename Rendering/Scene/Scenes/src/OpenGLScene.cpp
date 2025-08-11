#include "../include/OpenGLScene.hpp"
#include "../include/OpenGLSceneImpl.hpp"


namespace Andromeda::Rendering
{
	OpenGLScene::OpenGLScene()
		: m_pOpenGLSceneImpl{ new OpenGLScene::OpenGLSceneImpl() }
	{
	}

	OpenGLScene::~OpenGLScene()
	{
		delete m_pOpenGLSceneImpl;
	}

	bool OpenGLScene::StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const
	{
		return m_pOpenGLSceneImpl->StateChanged(objects);
	}

	float OpenGLScene::GetAmbientStrength() const
	{
		return m_pOpenGLSceneImpl->GetAmbientStrength();
	}

	void OpenGLScene::SetAmbientStrength(float ambientStrength)
	{
		m_pOpenGLSceneImpl->SetAmbientStrength(ambientStrength);
	}

	void OpenGLScene::ResizeGrid(float resizeFactor)
	{
		m_pOpenGLSceneImpl->ResizeGrid(resizeFactor);
	}

	const std::unordered_map<int, IRenderableObject*>& OpenGLScene::GetObjects() const
	{
		return m_pOpenGLSceneImpl->GetObjects();
	}

	void OpenGLScene::AddObject(int id, IRenderableObject* object)
	{
		m_pOpenGLSceneImpl->AddObject(id, object);
	}

	void OpenGLScene::RemoveObject(int id)
	{
		m_pOpenGLSceneImpl->RemoveObject(id);
	}

	void OpenGLScene::AddDirectionaLight(int id, DirectionalLight* pDirectionalLight)
	{
		m_pOpenGLSceneImpl->AddDirectionaLight(id, pDirectionalLight);
	}

	const std::unordered_map<int, const DirectionalLight*> OpenGLScene::GetDirectionalLights() const
	{
		return m_pOpenGLSceneImpl->GetDirectionalLights();
	}

	const std::unordered_map<int, const PointLight*> OpenGLScene::GetPointLights() const
	{
		return m_pOpenGLSceneImpl->GetPointLights();
	}

	const std::unordered_map<int, LuminousBehavior*>& OpenGLScene::GetLuminousObjects() const
	{
		return m_pOpenGLSceneImpl->GetLuminousObjects();
	}

	glm::vec3 OpenGLScene::GetSceneCenter() const
	{
		return m_pOpenGLSceneImpl->GetSceneCenter();;
	}
}
