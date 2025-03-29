#include "../include/LinearAlgebraOperations.hpp"


namespace Andromeda
{
	namespace Math
	{
		// === Dot Product ===
		float LinAlgOps::DotProd(const Vec2& a, const Vec2& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		float LinAlgOps::DotProd(const Vec3& a, const Vec3& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		float LinAlgOps::DotProd(const Vec4& a, const Vec4& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		// === Matrix * Vector ===
		Vec2 LinAlgOps::Multiply(const Mat2& mat, const Vec2& vec)
		{
			return {
				DotProd(mat.rows[0], vec),
				DotProd(mat.rows[1], vec)
			};
		}

		Vec3 LinAlgOps::Multiply(const Mat3& mat, const Vec3& vec)
		{
			return {
				DotProd(mat.rows[0], vec),
				DotProd(mat.rows[1], vec),
				DotProd(mat.rows[2], vec)
			};
		}

		Vec4 LinAlgOps::Multiply(const Mat4& mat, const Vec4& vec)
		{
			return {
				DotProd(mat.rows[0], vec),
				DotProd(mat.rows[1], vec),
				DotProd(mat.rows[2], vec),
				DotProd(mat.rows[3], vec)
			};
		}

		// === Matrix * Matrix ===
		Mat2 LinAlgOps::Multiply(const Mat2& a, const Mat2& b)
		{
			Mat2 result;
			for (int i = 0; i < 2; ++i)
			{
				result.rows[i] = {
					DotProd(a.rows[i], {b.rows[0].x, b.rows[1].x}),
					DotProd(a.rows[i], {b.rows[0].y, b.rows[1].y})
				};
			}
			return result;
		}

		Mat3 LinAlgOps::Multiply(const Mat3& a, const Mat3& b)
		{
			Mat3 result;
			for (int i = 0; i < 3; ++i)
			{
				result.rows[i] = {
					DotProd(a.rows[i], {b.rows[0].x, b.rows[1].x, b.rows[2].x}),
					DotProd(a.rows[i], {b.rows[0].y, b.rows[1].y, b.rows[2].y}),
					DotProd(a.rows[i], {b.rows[0].z, b.rows[1].z, b.rows[2].z})
				};
			}
			return result;
		}

		Mat4 LinAlgOps::Multiply(const Mat4& a, const Mat4& b)
		{
			Mat4 result;
			for (int i = 0; i < 4; ++i)
			{
				result.rows[i] = {
					DotProd(a.rows[i], {b.rows[0].x, b.rows[1].x, b.rows[2].x, b.rows[3].x}),
					DotProd(a.rows[i], {b.rows[0].y, b.rows[1].y, b.rows[2].y, b.rows[3].y}),
					DotProd(a.rows[i], {b.rows[0].z, b.rows[1].z, b.rows[2].z, b.rows[3].z}),
					DotProd(a.rows[i], {b.rows[0].w, b.rows[1].w, b.rows[2].w, b.rows[3].w})
				};
			}
			return result;
		}
	}
}
