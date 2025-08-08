#ifndef RENDERING__SCENE__HPP
#define RENDERING__SCENE__HPP


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
#include "../../Interfaces/include/IScene.hpp"
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
		void SetAmbientStrength(float ambientStrength) override;
		void ResizeGrid(float resizeFactor) override;

		// === From ISceneObjects ===
		const std::unordered_map<int, IRenderableObject*>& GetObjects() const override;
		void AddObject(int id, IRenderableObject* object) override;
		void RemoveObject(int id) override;

		// === From ISceneLighting ===
		const std::unordered_map<int, const DirectionalLight*> GetDirectionalLights() const override;
		const std::unordered_map<int, const PointLight*> GetPointLights() const override;
		const std::unordered_map<int, LuminousBehavior*>& GetLuminousObjects() const override;

	private:
		class OpenGLSceneImpl;
		OpenGLSceneImpl* m_pOpenGLSceneImpl;
	};
}


#endif // RENDERING__RENDERING__HPP