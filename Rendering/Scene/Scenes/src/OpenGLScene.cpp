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

	glm::vec4 OpenGLScene::GetBackgroundColor() const
	{
		return m_pOpenGLSceneImpl->GetBackgroundColor();
	}

	void OpenGLScene::SetAmbientStrength(float ambientStrength)
	{
		m_pOpenGLSceneImpl->SetAmbientStrength(ambientStrength);
	}

	void OpenGLScene::SetBackgroundColor(glm::vec4 backroundColor)
	{
		m_pOpenGLSceneImpl->SetBackgroundColor(backroundColor);
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

	void OpenGLScene::AddLuminousObject(int id, LuminousBehavior* pLuminousObject)
	{
		m_pOpenGLSceneImpl->AddLuminousObject(id, pLuminousObject);
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
