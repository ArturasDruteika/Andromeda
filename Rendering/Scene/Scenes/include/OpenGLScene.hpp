#ifndef RENDERING__SCENE__HPP
#define RENDERING__SCENE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "IScene.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API OpenGLScene
		: public IScene
	{
	public:
		OpenGLScene();
		~OpenGLScene();

		OpenGLScene(const OpenGLScene& other) = delete;	// Prevent Copy Constructor
		OpenGLScene& operator=(const OpenGLScene& other) = delete;	// Prevent Copy Assignment
		OpenGLScene(OpenGLScene&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLScene& operator=(OpenGLScene&& other) noexcept = delete;	// Prevent Move Assignment

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

		// === From IScene ===
		Math::Vec3 GetSceneCenter() const override;

	private:
		class OpenGLSceneImpl;
		OpenGLSceneImpl* m_pOpenGLSceneImpl;
	};
}


#endif // RENDERING__RENDERING__HPP