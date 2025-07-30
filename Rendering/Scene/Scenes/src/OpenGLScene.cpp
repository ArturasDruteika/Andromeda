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

	const std::unordered_map<int, IRenderableObject*>& OpenGLScene::GetLuminousObjects() const
	{
		return m_pOpenGLSceneImpl->GetLuminousObjects();
	}

	void OpenGLScene::AddDirectionalLight(
		int id,
		const Math::Vec3& direction,
		const Math::Vec3& color,
		float intensity,
		const Math::Vec3& ambient,
		const Math::Vec3& diffuse,
		const Math::Vec3& specular
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

	void OpenGLScene::RemoveDirectionalLight(int id)
	{
		m_pOpenGLSceneImpl->RemoveDirectionalLight(id);
	}
}
