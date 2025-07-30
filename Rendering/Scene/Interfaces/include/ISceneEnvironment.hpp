#ifndef ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP
#define ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP


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


namespace Andromeda::Rendering
{
	class RENDERING_API ISceneEnvironment
	{
	public:
		virtual ~ISceneEnvironment();

		// Getters
		virtual float GetAmbientStrength() const = 0;
		// Setters
		virtual void SetAmbientStrength(float ambientStrength) = 0;

		virtual void ResizeGrid(float resizeFactor) = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_ENVIRONMENT__HPP