// Myliu savo spoonchik spoonchik


#ifndef MATH__TRIGONOMETRY__HPP
#define MATH__TRIGONOMETRY__HPP


#if defined(_WIN32)
	#if defined(MATH_EXPORT)
		#define MATH_API __declspec(dllexport)
	#else
		#define MATH_API __declspec(dllimport)
	#endif /* MATH_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define MATH_API __attribute__((visibility("default")))
#endif




namespace Andromeda
{
	namespace Math
	{
		class MATH_API Trigonometry
		{
		public:
			static float Deg2Rad(float deg);
			static float Rad2Deg(float rad);
		};
	}
}


#endif // MATH__TRIGONOMETRY__HPP