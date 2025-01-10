#ifndef RENDERER__OPENGL_RENDERER__HPP
#define RENDERER__OPENGL_RENDERER__HPP


#if defined(_WIN32)
	#if defined(RENDERER_EXPORT)
		#define RENDERER_API __declspec(dllexport)
	#else
		#define RENDERER_API __declspec(dllimport)
	#endif /* RENDERER_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERER_API __attribute__((visibility("default")))
#endif


#include <glad/gl.h>


namespace Andromeda
{
	namespace Renderer
	{
		class RENDERER_API OpenGLRenderer
		{
		public:
			OpenGLRenderer();
			~OpenGLRenderer();

			OpenGLRenderer(const OpenGLRenderer& other);            // Copy Constructor
			OpenGLRenderer& operator=(const OpenGLRenderer& other); // Copy Assignment
			OpenGLRenderer(OpenGLRenderer&& other) noexcept;        // Move Constructor
			OpenGLRenderer& operator=(OpenGLRenderer&& other) noexcept; // Move Assignment

			bool IsInitialized() const;
			void Initialize(GLADloadfunc load);
			void RenderFrame();
			void Shutdown();

		private:
			class OpenGLRendererImpl;
			OpenGLRendererImpl* m_pOpenGLRendererImpl;
		};
	}
}


#endif // RENDERER__OPENGL_RENDERER__HPP