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
#include "../../RenderableObjects/incldue/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IScene
	{
	public:
		virtual ~IScene();

		// Getters
		virtual bool StateChanged() const;
		virtual float GetAmbientStrength() const;
		virtual const std::unordered_map<int, IRenderableObjectOpenGL*>& GetObjects() const;
		virtual const std::unordered_map<int, IRenderableObjectOpenGL*>& GetLuminousObjects() const;
		// Setters
		virtual void SetAmbientStrength(float ambientStrength);
		virtual void ResetState();

		virtual void AddObject(int id, IRenderableObjectOpenGL* object);
		virtual void RemoveObject(int id);
		virtual void AddDirectionalLight(
			int id,
			const glm::vec3& direction,
			const glm::vec3& color = glm::vec3{ 1.0f },
			float intensity = 1.0f,
			const glm::vec3& ambient = glm::vec3(0.1f),
			const glm::vec3& diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
			const glm::vec3& specular = glm::vec3(0.4f, 0.4f, 0.4f)
		);
		virtual void RemoveDrectionalLight(int id);
		virtual void ResizeGrid(float resizeFactor);
	};
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP