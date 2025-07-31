#ifndef RENDERER__I_RENDERER__HPP
#define RENDERER__I_RENDERER__HPP


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


#include "../include/IGridControl.hpp"
#include "../include/IIlluminationControl.hpp"
#include "../../../Scene/Interfaces/include/IScene.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IRenderer
		: public IGridControl
		, public IIlluminationControl
	{
	public:
		virtual ~IRenderer();

		// Getters
		virtual bool IsInitialized() const = 0;

		virtual void Init() = 0;
		virtual void DeInit() = 0;
		virtual void RenderFrame(IScene& scene) = 0;
		virtual void Resize(int width, int height) = 0;
	};
}


#endif // RENDERER__I_RENDERER__HPP