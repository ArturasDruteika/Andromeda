#ifndef RENDERER__I_SIZE__HPP
#define RENDERER__I_SIZE__HPP


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
	class RENDERING_API ISizeControl
	{
	public:
		virtual ~ISizeControl();

		// Getters
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Resize(int width, int height) = 0;
	};
}


#endif // RENDERER__I_SIZE__HPP