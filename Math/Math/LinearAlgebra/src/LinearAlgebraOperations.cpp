#include "../include/LinearAlgebraOperations.hpp"


namespace Andromeda
{
	namespace Math
	{
		float LinAlgOps::DotProd(const Vec2& a, const Vec2& b)
		{
			return a[0] * b[0] + a[1] * b[1];
		}

		float LinAlgOps::DotProd(const Vec3& a, const Vec3& b)
		{
			return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
		}

		float LinAlgOps::DotProd(const Vec4& a, const Vec4& b)
		{
			return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
		}

		Vec2 LinAlgOps::Multiply(const Mat2& mat, const Vec2& vec)
		{
			return Vec2{
				DotProd(mat[0], vec),
				DotProd(mat[1], vec)
			};
		}

		Vec3 LinAlgOps::Multiply(const Mat3& mat, const Vec3& vec)
		{
			return Vec3{
				DotProd(mat[0], vec),
				DotProd(mat[1], vec),
				DotProd(mat[2], vec)
			};
		}

		Vec4 LinAlgOps::Multiply(const Mat4& mat, const Vec4& vec)
		{
			return Vec4{
				DotProd(mat[0], vec),
				DotProd(mat[1], vec),
				DotProd(mat[2], vec),
				DotProd(mat[3], vec)
			};
		}

		// === Matrix * Matrix ===
		Mat2 LinAlgOps::Multiply(const Mat2& a, const Mat2& b)
		{
			Mat2 result;
			for (int i = 0; i < 2; ++i)
			{
				Vec2 col0 = { b[0][0], b[1][0] };
				Vec2 col1 = { b[0][1], b[1][1] };

				result[i] = {
					DotProd(a[i], col0),
					DotProd(a[i], col1)
				};
			}
			return result;
		}

		Mat3 LinAlgOps::Multiply(const Mat3& a, const Mat3& b)
		{
			Mat3 result;
			for (int i = 0; i < 3; ++i)
			{
				Vec3 col0 = { b[0][0], b[1][0], b[2][0] };
				Vec3 col1 = { b[0][1], b[1][1], b[2][1] };
				Vec3 col2 = { b[0][2], b[1][2], b[2][2] };

				result[i] = {
					DotProd(a[i], col0),
					DotProd(a[i], col1),
					DotProd(a[i], col2)
				};
			}
			return result;
		}

		Mat4 LinAlgOps::Multiply(const Mat4& a, const Mat4& b)
		{
			Mat4 result;
			for (int i = 0; i < 4; ++i)
			{
				Vec4 col0 = { b[0][0], b[1][0], b[2][0], b[3][0] };
				Vec4 col1 = { b[0][1], b[1][1], b[2][1], b[3][1] };
				Vec4 col2 = { b[0][2], b[1][2], b[2][2], b[3][2] };
				Vec4 col3 = { b[0][3], b[1][3], b[2][3], b[3][3] };

				result[i] = {
					DotProd(a[i], col0),
					DotProd(a[i], col1),
					DotProd(a[i], col2),
					DotProd(a[i], col3)
				};
			}
			return result;
		}

		// === Length ===
		float LinAlgOps::Length(const Vec2& v)
		{
			return std::sqrt(DotProd(v, v));
		}

		float LinAlgOps::Length(const Vec3& v)
		{
			return std::sqrt(DotProd(v, v));
		}

		float LinAlgOps::Length(const Vec4& v)
		{
			return std::sqrt(DotProd(v, v));
		}

		// === Normalize ===
		Vec2 LinAlgOps::Normalize(const Vec2& v, float epsilon)
		{
			float lenSq = DotProd(v, v);
			if (lenSq <= epsilon * epsilon)
			{
				return v; // Avoid NaNs on zero-length vectors
			}
			float invLen = 1.0f / std::sqrt(lenSq);
			return Vec2{ v[0] * invLen, v[1] * invLen };
		}

		Vec3 LinAlgOps::Normalize(const Vec3& v, float epsilon)
		{
			float lenSq = DotProd(v, v);
			if (lenSq <= epsilon * epsilon)
			{
				return v;
			}
			float invLen = 1.0f / std::sqrt(lenSq);
			return Vec3{ v[0] * invLen, v[1] * invLen, v[2] * invLen };
		}

		Vec4 LinAlgOps::Normalize(const Vec4& v, float epsilon)
		{
			float lenSq = DotProd(v, v);
			if (lenSq <= epsilon * epsilon)
			{
				return v;
			}
			float invLen = 1.0f / std::sqrt(lenSq);
			return Vec4{ v[0] * invLen, v[1] * invLen, v[2] * invLen, v[3] * invLen };
		}
	}
}
