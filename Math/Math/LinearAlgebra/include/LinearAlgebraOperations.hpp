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

			// Cross product (3D)
			static Vec3 Cross(const Vec3& a, const Vec3& b);

			// Rotate vector around axis by angle (glm::rotate(vec, angle, axis))
			static Vec2 Rotate(const Vec2& v, float angleRadians);
			static Vec3 Rotate(const Vec3& v, float angleRadians, const Vec3& axis);
			static Vec4 Rotate(const Vec4& v, float angleRadians, const Vec3& axis);

			// Projection matrix (OpenGL-style)
			static Mat4 Perspective(float fovYRadians, float aspect, float zNear, float zFar);

			// View matrix (glm::lookAt analog, OpenGL-style RH, -Z forward, Y up)
			static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

			// Clamps a value between minValue and maxValue
			template <typename T>
			static T Clamp(const T& value, const T& minValue, const T& maxValue)
			{
				if (value < minValue)
				{
					return minValue;
				}
				if (value > maxValue)
				{
					return maxValue;
				}
				return value;
			}
		};
	}
}


#endif // MATH__MATH_OPERATIONS__HPP