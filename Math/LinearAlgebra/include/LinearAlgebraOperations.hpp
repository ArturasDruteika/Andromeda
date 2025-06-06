#ifndef MATH__MATH_OPERATIONS__HPP
#define MATH__MATH_OPERATIONS__HPP


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


#include "../include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Math
	{
		class MATH_API LinAlgOps
		{
		public:
			// Vector-Vector Dot Products
			static float DotProd(const Vec2& a, const Vec2& b);
			static float DotProd(const Vec3& a, const Vec3& b);
			static float DotProd(const Vec4& a, const Vec4& b);
			// Vector-Matrix Multiplication
			static Vec2 Multiply(const Mat2& mat, const Vec2& vec);
			static Vec3 Multiply(const Mat3& mat, const Vec3& vec);
			static Vec4 Multiply(const Mat4& mat, const Vec4& vec);
			// Matrix-Matrix Multiplication
			static Mat2 Multiply(const Mat2& a, const Mat2& b);
			static Mat3 Multiply(const Mat3& a, const Mat3& b);
			static Mat4 Multiply(const Mat4& a, const Mat4& b);
		};
	}
}


#endif // MATH__MATH_OPERATIONS__HPP