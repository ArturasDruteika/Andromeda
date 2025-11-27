#include "../include/SceneOpenGL.hpp"
#include "../include/SceneOpenGLImpl.hpp"


namespace Andromeda::Rendering
{
	SceneOpenGL::SceneOpenGL()
		: m_pSceneOpenGLImpl{ new SceneOpenGL::SceneOpenGLImpl() }
	{
	}

	SceneOpenGL::~SceneOpenGL()
	{
		delete m_pSceneOpenGLImpl;
	}

	bool SceneOpenGL::StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const
	{
		return m_pSceneOpenGLImpl->StateChanged(objects);
	}

	float SceneOpenGL::GetAmbientStrength() const
	{
		return m_pSceneOpenGLImpl->GetAmbientStrength();
	}

	const Math::Vec4& SceneOpenGL::GetBackgroundColor() const
	{
		return m_pSceneOpenGLImpl->GetBackgroundColor();
	}

	void SceneOpenGL::SetAmbientStrength(float ambientStrength)
	{
		m_pSceneOpenGLImpl->SetAmbientStrength(ambientStrength);
	}

	void SceneOpenGL::SetBackgroundColor(const Math::Vec4& backroundColor)
	{
		m_pSceneOpenGLImpl->SetBackgroundColor(backroundColor);
	}

	void SceneOpenGL::ResizeGrid(float resizeFactor)
	{
		m_pSceneOpenGLImpl->ResizeGrid(resizeFactor);
	}

	const std::unordered_map<int, IRenderableObject*>& SceneOpenGL::GetObjects() const
	{
		return m_pSceneOpenGLImpl->GetObjects();
	}

	void SceneOpenGL::AddObject(int id, IRenderableObject* object)
	{
		m_pSceneOpenGLImpl->AddObject(id, object);
	}

	void SceneOpenGL::RemoveObject(int id)
	{
		m_pSceneOpenGLImpl->RemoveObject(id);
	}

	void SceneOpenGL::AddLuminousObject(int id, Space::LuminousBehavior* pLuminousObject)
	{
		m_pSceneOpenGLImpl->AddLuminousObject(id, pLuminousObject);
	}

	const std::unordered_map<int, const Space::DirectionalLight*> SceneOpenGL::GetDirectionalLights() const
	{
		return m_pSceneOpenGLImpl->GetDirectionalLights();
	}

	const std::unordered_map<int, const Space::PointLight*> SceneOpenGL::GetPointLights() const
	{
		return m_pSceneOpenGLImpl->GetPointLights();
	}

	const std::unordered_map<int, Space::LuminousBehavior*>& SceneOpenGL::GetLuminousObjects() const
	{
		return m_pSceneOpenGLImpl->GetLuminousObjects();
	}

	void SceneOpenGL::ClearScene()
	{
	}

	void SceneOpenGL::ResetSceneState()
	{
	}

	ICamera* SceneOpenGL::GetActiveCamera()
	{
		return nullptr;
	}

	void SceneOpenGL::SetActiveCamera(ICamera* camera)
	{
	}

	Math::Vec3 SceneOpenGL::GetSceneCenter() const
	{
		return m_pSceneOpenGLImpl->GetSceneCenter();;
	}
}
