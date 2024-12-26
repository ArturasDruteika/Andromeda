#ifndef WINDOW_WINDOW__HPP
#define WINDOW_WINDOW__HPP


#if defined(_WIN32)
	#if defined(WINDOW_EXPORT)
		#define WINDOW_API __declspec(dllexport)
	#else
		#define WINDOW_API __declspec(dllimport)
	#endif /* WINDOW_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
// GCC
#define WINDOW_API __attribute__((visibility("default")))
#endif


namespace Andromeda
{
	namespace Window
	{
		class WINDOW_API Window
		{
		public:
			Window();
			~Window();

		private:

		};
	}
}


#endif // WINDOW_WINDOW__HPP