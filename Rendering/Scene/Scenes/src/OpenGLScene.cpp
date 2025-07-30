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

	bool OpenGLScene::StateChanged() const
	{
		return m_pOpenGLSceneImpl->StateChanged();
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

	void OpenGLScene::ResetState()
	{
		m_pOpenGLSceneImpl->ResetState();
	}

	void OpenGLScene::AddObject(int id, IRenderableObjectOpenGL* object)
	{
		m_pOpenGLSceneImpl->AddObject(id, object);
	}

	void OpenGLScene::RemoveObject(int id)
	{
		m_pOpenGLSceneImpl->RemoveObject(id);
	}

	void OpenGLScene::AddDirectionalLight(
		int id, 
		const glm::vec3& direction, 
		const glm::vec3& color, 
		float intensity, 
		const glm::vec3& ambient, 
		const glm::vec3& diffuse, 
		const glm::vec3& specular
	)
	{
		m_pOpenGLSceneImpl->AddDirectionalLight(
			id,
			direction,
			color,
			intensity,
			ambient,
			diffuse,
			specular
		);
	}

	void OpenGLScene::RemoveDrectionalLight(int id)
	{
		m_pOpenGLSceneImpl->RemoveDrectionalLight(id);
	}

	void OpenGLScene::ResizeGrid(float resizeFactor)
	{
		m_pOpenGLSceneImpl->ResizeGrid(resizeFactor);
	}
}
