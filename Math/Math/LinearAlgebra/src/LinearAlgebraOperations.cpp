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

		Vec3 LinAlgOps::Cross(const Vec3& a, const Vec3& b)
		{
			return Vec3
			{
				a[1] * b[2] - a[2] * b[1],
				a[2] * b[0] - a[0] * b[2],
				a[0] * b[1] - a[1] * b[0]
			};
		}

		Vec2 LinAlgOps::Rotate(const Vec2& v, float angleRadians)
		{
			float cosA = std::cos(angleRadians);
			float sinA = std::sin(angleRadians);

			return Vec2
			{
				v[0] * cosA - v[1] * sinA,
				v[0] * sinA + v[1] * cosA
			};
		}

		Vec3 LinAlgOps::Rotate(const Vec3& v, float angleRadians, const Vec3& axis)
		{
			// Equivalent to glm::rotate(v, angle, axis)
			// Uses Rodrigues rotation formula.

			Vec3 axisNorm = Normalize(axis);
			float cosA = std::cos(angleRadians);
			float sinA = std::sin(angleRadians);

			// term1 = v * cosA
			Vec3 term1
			{
				v[0] * cosA,
				v[1] * cosA,
				v[2] * cosA
			};

			// term2 = cross(axis, v) * sinA
			Vec3 crossAv = Cross(axisNorm, v);
			Vec3 term2
			{
				crossAv[0] * sinA,
				crossAv[1] * sinA,
				crossAv[2] * sinA
			};

			// term3 = axis * dot(axis, v) * (1 - cosA)
			float dotAv = DotProd(axisNorm, v);
			float k = (1.0f - cosA) * dotAv;
			Vec3 term3
			{
				axisNorm[0] * k,
				axisNorm[1] * k,
				axisNorm[2] * k
			};

			return Vec3
			{
				term1[0] + term2[0] + term3[0],
				term1[1] + term2[1] + term3[1],
				term1[2] + term2[2] + term3[2]
			};
		}

		Vec4 LinAlgOps::Rotate(const Vec4& v, float angleRadians, const Vec3& axis)
		{
			Vec3 xyz{ v[0], v[1], v[2] };

			Vec3 rotated = Rotate(xyz, angleRadians, axis);

			return Vec4
			{
				rotated[0],
				rotated[1],
				rotated[2],
				v[3]   // w unchanged
			};
		}

		Mat4 LinAlgOps::Perspective(float fovYRadians, float aspect, float zNear, float zFar)
		{
			// Basic safety: avoid division by zero or nonsense parameters
			const float epsilon = 1e-6f;
			if (aspect <= epsilon)
			{
				// You might want to assert or log here in your real engine
				return Mat4{};
			}

			if (zNear <= 0.0f || zFar <= zNear)
			{
				// Also a good place for an assert/log
				return Mat4{};
			}

			const float tanHalfFovY = std::tan(fovYRadians * 0.5f);
			if (std::abs(tanHalfFovY) <= epsilon)
			{
				return Mat4{};
			}

			const float f = 1.0f / tanHalfFovY;

			Mat4 result;

			// Row 0
			result[0] = Vec4
			{
				f / aspect,
				0.0f,
				0.0f,
				0.0f
			};

			// Row 1
			result[1] = Vec4
			{
				0.0f,
				f,
				0.0f,
				0.0f
			};

			// Row 2
			result[2] = Vec4
			{
				0.0f,
				0.0f,
				(zFar + zNear) / (zNear - zFar),
				-1.0f
			};

			// Row 3
			result[3] = Vec4
			{
				0.0f,
				0.0f,
				(2.0f * zFar * zNear) / (zNear - zFar),
				0.0f
			};

			return result;
		}

		Mat4 LinAlgOps::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
		{
			// Forward vector (from eye to center)
			Vec3 f = Normalize(center - eye);
			// Side vector
			Vec3 s = Normalize(Cross(f, up));
			// Recomputed orthonormal up vector
			Vec3 u = Cross(s, f);

			Mat4 result;

			// Row 0
			result[0] = Vec4
			{
				s[0],
				s[1],
				s[2],
				-DotProd(s, eye)
			};

			// Row 1
			result[1] = Vec4
			{
				u[0],
				u[1],
				u[2],
				-DotProd(u, eye)
			};

			// Row 2
			result[2] = Vec4
			{
				-f[0],
				-f[1],
				-f[2],
				DotProd(f, eye)
			};

			// Row 3
			result[3] = Vec4
			{
				0.0f,
				0.0f,
				0.0f,
				1.0f
			};

			return result;
		}
	}
}
