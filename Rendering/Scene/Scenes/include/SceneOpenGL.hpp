#ifndef RENDERING__SCENE__HPP
#define RENDERING__SCENE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "Andromeda/Scene/IScene.hpp"
#include "LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API SceneOpenGL
		: public IScene
	{
	public:
		SceneOpenGL();
		~SceneOpenGL();

		SceneOpenGL(const SceneOpenGL& other) = delete;	// Prevent Copy Constructor
		SceneOpenGL& operator=(const SceneOpenGL& other) = delete;	// Prevent Copy Assignment
		SceneOpenGL(SceneOpenGL&& other) noexcept = delete;	// Prevent Move Constructor
		SceneOpenGL& operator=(SceneOpenGL&& other) noexcept = delete;	// Prevent Move Assignment

		// === From ISceneState ===
		bool StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const override;

		// === From ISceneEnvironment ===
		float GetAmbientStrength() const override;
		const Math::Vec4& GetBackgroundColor() const override;
		void SetAmbientStrength(float ambientStrength) override;
		void SetBackgroundColor(const Math::Vec4& backroundColor) override;
		void ResizeGrid(float resizeFactor) override;

		// === From ISceneObjects ===
		const std::unordered_map<int, IRenderableObject*>& GetObjects() const override;
		void AddObject(int id, IRenderableObject* object) override;
		void RemoveObject(int id) override;
		void AddLuminousObject(int id, PhysicalProperties::LuminousBehavior* pLuminousObject) override;

		// === From ISceneLighting ===
		const std::unordered_map<int, const PhysicalProperties::DirectionalLight*> GetDirectionalLights() const override;
		const std::unordered_map<int, const PhysicalProperties::PointLight*> GetPointLights() const override;
		const std::unordered_map<int, PhysicalProperties::LuminousBehavior*>& GetLuminousObjects() const override;

		void ClearScene() override;
		void ResetSceneState() override;

		// === From ICameraHandler ===
		ICamera* GetActiveCamera()override;
		void SetActiveCamera(ICamera* camera) override;

		// === From IScene ===
		Math::Vec3 GetSceneCenter() const override;

	private:
		class SceneOpenGLImpl;
		SceneOpenGLImpl* m_pSceneOpenGLImpl;
	};
}


#endif // RENDERING__RENDERING__HPP