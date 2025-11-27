#ifndef RENDERING__OPENGL_LOADER__HPP
#define RENDERING__OPENGL_LOADER__HPP


#include "../../MacroExports/include/MacroExports.hpp"
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
			bool IsInitialized() const;

		private:
			class OpenGLLoaderImpl;
			OpenGLLoaderImpl* m_pOpenGLLoaderImpl;
		};
	}
}


#endif // RENDERING__OPENGL_LOADER__HPP