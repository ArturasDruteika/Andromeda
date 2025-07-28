#ifndef RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP
#define RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP



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
#include "IRenderableObject.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API IRenderableObjectOpenGL
			: public IRenderableObject
		{	
		public:
			IRenderableObjectOpenGL();
			virtual ~IRenderableObjectOpenGL();

			// Getters
			virtual unsigned int GetVBO() const = 0;
			virtual unsigned int GetVAO() const = 0;
			virtual unsigned int GetEBO() const = 0;
		};
	}
}


#endif // RENDERING__I_RENDERABLE_OBJECT_OPEN_GL__HPP