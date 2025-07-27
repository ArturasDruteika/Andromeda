#ifndef RENDERER__I_ILLUMINATION_CONTROL__HPP
#define RENDERER__I_ILLUMINATION_CONTROL__HPP


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
	class RENDERING_API IIlluminationControl
	{
	public:
		virtual ~IIlluminationControl();

		// Getters
		virtual bool IsIlluminationMode() const = 0;
		// Setters
		virtual void SetIlluminationMode(bool mode) = 0;
	};
}


#endif // RENDERER__I_ILLUMINATION_CONTROL__HPP