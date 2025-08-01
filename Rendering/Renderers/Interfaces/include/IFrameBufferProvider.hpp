#ifndef RENDERER__I_FRAMEBUFFER_PROVIDER__HPP
#define RENDERER__I_FRAMEBUFFER_PROVIDER__HPP


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
	class RENDERING_API IFrameBufferProvider
	{
	public:
		virtual ~IFrameBufferProvider();

		// Getters
		virtual unsigned int GetFrameBufferTexture() const = 0;
		virtual unsigned int GetFrameBufferID() const = 0;
	};
}


#endif // RENDERER__I_FRAMEBUFFER_PROVIDER__HPP