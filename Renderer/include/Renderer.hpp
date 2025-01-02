#ifndef RENDERER__RENDERER__HPP
#define RENDERER__RENDERER__HPP


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


namespace Andromeda
{
	namespace Renderer
	{
		class RENDERER_API Renderer
		{
		public:
			Renderer();
			~Renderer();

		private:
			class RendererImpl;
			RendererImpl* m_pRendererImpl;
		};
	}
}


#endif // RENDERER__RENDERER__HPP