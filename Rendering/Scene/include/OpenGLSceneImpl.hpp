#ifndef ENVIRONMENT__SCENE_IMPL__HPP
#define ENVIRONMENT__SCENE_IMPL__HPP


#include "../include/OpenGLScene.hpp"
#include "../../Light/include/LuminousBehavior.hpp"
#include "../../Light/include/DirectionalLight.hpp"


namespace Andromeda::Rendering
{
	class OpenGLScene::OpenGLSceneImpl
	{
	public:
		OpenGLSceneImpl();
		~OpenGLSceneImpl();

		OpenGLSceneImpl(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Constructor
		OpenGLSceneImpl& operator=(const OpenGLSceneImpl& other) = delete;	// Prevent Copy Assignment
		OpenGLSceneImpl(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLSceneImpl& operator=(OpenGLSceneImpl&& other) noexcept = delete;	// Prevent Move Assignment

		// Getters
		float GetAmbientStrength() const;
		const std::unordered_map<int, IRenderableObjectOpenGL*>& GetObjects() const;
		const std::unordered_map<int, IRenderableObjectOpenGL*>& GetLuminousObjects() const;
		const std::unordered_map<int, DirectionalLight>& GetDirectionalLights() const;
		// Setters
		void SetAmbientStrength(float ambientStrength);

		void AddObject(int id, IRenderableObjectOpenGL* object);
		void RemoveObject(int id);
		void AddDirectionalLight(
			int id,
			const glm::vec3& direction,
			const glm::vec3& color = glm::vec3{ 1.0f },
			float intensity = 1.0f,
			const glm::vec3& ambient = glm::vec3(0.1f),
			const glm::vec3& diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
			const glm::vec3& specular = glm::vec3(0.4f, 0.4f, 0.4f)
		);
		void RemoveDrectionalLight(int id);
		void ResizeGrid(float resizeFactor);

	private:
		float m_gridSpacing;
		float m_ambientStrength;
		std::unordered_map<int, IRenderableObjectOpenGL*> m_renderableObjsPtrsMap;
		std::unordered_map<int, IRenderableObjectOpenGL*> m_luminousObjsPtrsMap;
		std::unordered_map<int, DirectionalLight> m_directionalLights;
	};
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP