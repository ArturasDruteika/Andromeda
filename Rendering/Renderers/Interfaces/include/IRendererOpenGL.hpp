#ifndef RENDERER__I_RENDERER_OPENGL__HPP
#define RENDERER__I_RENDERER_OPENGL__HPP


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


#include "../include/IRenderer.hpp"
#include "../include/IFrameBufferProvider.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IRendererOpenGL
		: public IRenderer
		, public IFrameBufferProvider
	{
	public:
		virtual ~IRendererOpenGL();
	};
}


#endif // RENDERER__I_RENDERER_OPENGL__HPP