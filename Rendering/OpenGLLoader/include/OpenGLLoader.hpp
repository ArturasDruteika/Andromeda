#ifndef RENDERING__OPENGL_LOADER__HPP
#define RENDERING__OPENGL_LOADER__HPP


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


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API OpenGLLoader
		{
		public:
			OpenGLLoader();
			~OpenGLLoader();

			OpenGLLoader(const OpenGLLoader& other) = delete;	// Prevent Copy Constructor
			OpenGLLoader& operator=(const OpenGLLoader& other) = delete;	// Prevent Copy Assignment
			OpenGLLoader(OpenGLLoader&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLLoader& operator=(OpenGLLoader&& other) noexcept = delete;	// Prevent Move Assignment

			void LoadGlad(const char* name);
			bool Initialize() const;

		private:
			class OpenGLLoaderImpl;
			OpenGLLoaderImpl* m_pOpenGLLoaderImpl;
		};
	}
}


#endif // RENDERING__OPENGL_LOADER__HPP