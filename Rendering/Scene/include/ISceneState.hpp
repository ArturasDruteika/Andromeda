#ifndef ENVIRONMENT__I_SCENE_STATE__HPP
#define ENVIRONMENT__I_SCENE_STATE__HPP


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
	class RENDERING_API ISceneState
	{
	public:
		virtual ~ISceneState();

		virtual bool StateChanged() const = 0;
		virtual void ResetState() = 0;
	};
}


#endif // ENVIRONMENT__I_SCENE_STATE__HPP