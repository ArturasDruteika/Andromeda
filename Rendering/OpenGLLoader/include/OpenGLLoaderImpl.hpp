#ifndef RENDERING__OPENGL_LOADER_IMPL__HPP
#define RENDERING__OPENGL_LOADER_IMPL__HPP


#include "OpenGLLoader.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLLoader::OpenGLLoaderImpl
		{
		public:
			OpenGLLoaderImpl();
			~OpenGLLoaderImpl();

			OpenGLLoaderImpl(const OpenGLLoaderImpl& other) = delete;	// Prevent Copy Constructor
			OpenGLLoaderImpl& operator=(const OpenGLLoaderImpl& other) = delete;	// Prevent Copy Assignment
			OpenGLLoaderImpl(OpenGLLoaderImpl&& other) noexcept = delete;	// Prevent Move Constructor
			OpenGLLoaderImpl& operator=(OpenGLLoaderImpl&& other) noexcept = delete;	// Prevent Move Assignment

			void LoadGlad(const char* name);
			bool Initialize() const;

		private:
			bool m_isInitialized;
		};
	}
}


#endif // RENDERING__OPENGL_LOADER_IMPL__HPP