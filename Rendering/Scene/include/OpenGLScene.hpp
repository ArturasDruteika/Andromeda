#ifndef ENVIRONMENT__SCENE__HPP
#define ENVIRONMENT__SCENE__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "../../RenderableObjects/include/IRenderableObjectOpenGL.hpp"
#include "../../Light/include/LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API OpenGLScene
	{
	public:
		OpenGLScene();
		~OpenGLScene();

		OpenGLScene(const OpenGLScene& other) = delete;	// Prevent Copy Constructor
		OpenGLScene& operator=(const OpenGLScene& other) = delete;	// Prevent Copy Assignment
		OpenGLScene(OpenGLScene&& other) noexcept = delete;	// Prevent Move Constructor
		OpenGLScene& operator=(OpenGLScene&& other) noexcept = delete;	// Prevent Move Assignment

		// Getters
		float GetAmbientStrength() const;
		const std::unordered_map<int, IRenderableObjectOpenGL*>& GetObjects() const;
		const std::unordered_map<int, IRenderableObjectOpenGL*>& GetLuminousObjects() const;
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
		class OpenGLSceneImpl;
		OpenGLSceneImpl* m_pOpenGLSceneImpl;
	};
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP