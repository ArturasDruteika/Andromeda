#ifndef MATH__MATH_OPERATIONS__HPP
#define MATH__MATH_OPERATIONS__HPP


#include "../../MacroExports/include/MacroExports.hpp"
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

			// Length / magnitude
			static float Length(const Vec2& v);
			static float Length(const Vec3& v);
			static float Length(const Vec4& v);

			// Normalize (returns unit vector). If length is ~0, returns the input unchanged.
			static Vec2 Normalize(const Vec2& v, float epsilon = 1e-8f);
			static Vec3 Normalize(const Vec3& v, float epsilon = 1e-8f);
			static Vec4 Normalize(const Vec4& v, float epsilon = 1e-8f);
		};
	}
}


#endif // MATH__MATH_OPERATIONS__HPP