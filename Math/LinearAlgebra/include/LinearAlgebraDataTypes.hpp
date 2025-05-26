#ifndef MATH__MATH_DATA_TYPES__HPP
#define MATH__MATH_DATA_TYPES__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Math
		// Linear Algebra Data Types
		// These are simple data structures for 2D, 3D, and 4D vectors and matrices.
		// ATM they are not optimized for performance but are easy to use and understand.
		// In a real-world application, you might want to use a more optimized library like GLM or Eigen.
	{
		struct Vec2
		{
			std::array<float, 2> data;

			Vec2(float x, float y) : data{ x, y } {}
			Vec2() : data{ 0.0f, 0.0f } {}
			Vec2(const Vec2& other) : data{ other.data[0], other.data[1] } {}

			float& operator[](int index) { return data[index]; }
			const float& operator[](int index) const { return data[index]; }

			Vec2& operator+=(const Vec2& other)
			{
				data[0] += other[0];
				data[1] += other[1];
				return *this;
			}

			Vec2& operator-=(const Vec2& other)
			{
				data[0] -= other[0];
				data[1] -= other[1];
				return *this;
			}

			friend Vec2 operator+(Vec2 lhs, const Vec2& rhs)
			{
				return lhs += rhs;
			}

			friend Vec2 operator-(Vec2 lhs, const Vec2& rhs)
			{
				return lhs -= rhs;
			}

			bool operator==(const Vec2& other) const
			{
				return data[0] == other.data[0] && data[1] == other.data[1];
			}

			bool operator!=(const Vec2& other) const
			{
				return !(*this == other);
			}
		};

		struct Vec3
		{
			std::array<float, 3> data;

			Vec3(float x, float y, float z) : data{ x, y, z } {}
			Vec3() : data{ 0.0f, 0.0f, 0.0f } {}
			Vec3(const Vec3& other) : data{ other.data[0], other.data[1], other.data[2] } {}

			float& operator[](int index) { return data[index]; }
			const float& operator[](int index) const { return data[index]; }

			Vec3& operator+=(const Vec3& other)
			{
				data[0] += other[0];
				data[1] += other[1];
				data[2] += other[2];
				return *this;
			}

			Vec3& operator-=(const Vec3& other)
			{
				data[0] -= other[0];
				data[1] -= other[1];
				data[2] -= other[2];
				return *this;
			}

			friend Vec3 operator+(Vec3 lhs, const Vec3& rhs)
			{
				return lhs += rhs;
			}

			friend Vec3 operator-(Vec3 lhs, const Vec3& rhs)
			{
				return lhs -= rhs;
			}

			bool operator==(const Vec3& other) const
			{
				return data[0] == other.data[0] &&
					data[1] == other.data[1] &&
					data[2] == other.data[2];
			}

			bool operator!=(const Vec3& other) const
			{
				return !(*this == other);
			}
		};

		struct Vec4
		{
			std::array<float, 4> data;

			Vec4(float x, float y, float z, float w) : data{ x, y, z, w } {}
			Vec4() : data{ 0.0f, 0.0f, 0.0f, 0.0f } {}
			Vec4(const Vec4& other) : data{ other.data[0], other.data[1], other.data[2], other.data[3] } {}

			float& operator[](int index) { return data[index]; }
			const float& operator[](int index) const { return data[index]; }

			Vec4& operator+=(const Vec4& other)
			{
				data[0] += other[0];
				data[1] += other[1];
				data[2] += other[2];
				data[3] += other[3];
				return *this;
			}

			Vec4& operator-=(const Vec4& other)
			{
				data[0] -= other[0];
				data[1] -= other[1];
				data[2] -= other[2];
				data[3] -= other[3];
				return *this;
			}

			friend Vec4 operator+(Vec4 lhs, const Vec4& rhs)
			{
				return lhs += rhs;
			}

			friend Vec4 operator-(Vec4 lhs, const Vec4& rhs)
			{
				return lhs -= rhs;
			}

			bool operator==(const Vec4& other) const
			{
				return data[0] == other.data[0] &&
					data[1] == other.data[1] &&
					data[2] == other.data[2] &&
					data[3] == other.data[3];
			}

			bool operator!=(const Vec4& other) const
			{
				return !(*this == other);
			}
		};

		struct Mat2
		{
			std::array<Vec2, 2> data;

			Mat2() : data{ Vec2(), Vec2() } {}
			Mat2(const Vec2& row0, const Vec2& row1) : data{ row0, row1 } {}
			Mat2(const Mat2& other) : data{ other.data[0], other.data[1] } {}

			Vec2& operator[](int index) { return data[index]; }
			const Vec2& operator[](int index) const { return data[index]; }

			bool operator==(const Mat2& other) const
			{
				return data[0] == other.data[0] && data[1] == other.data[1];
			}

			bool operator!=(const Mat2& other) const
			{
				return !(*this == other);
			}
		};

		struct Mat3
		{
			std::array<Vec3, 3> data;

			Mat3() : data{ Vec3(), Vec3(), Vec3() } {}
			Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2) : data{ row0, row1, row2 } {}
			Mat3(const Mat3& other) : data{ other.data[0], other.data[1], other.data[2] } {}

			Vec3& operator[](int index) { return data[index]; }
			const Vec3& operator[](int index) const { return data[index]; }

			bool operator==(const Mat3& other) const
			{
				return data[0] == other.data[0] &&
					data[1] == other.data[1] &&
					data[2] == other.data[2];
			}

			bool operator!=(const Mat3& other) const
			{
				return !(*this == other);
			}
		};

		struct Mat4
		{
			std::array<Vec4, 4> data;

			Mat4() : data{ Vec4(), Vec4(), Vec4(), Vec4() } {}
			Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3) : data{ row0, row1, row2, row3 } {}
			Mat4(const Mat4& other) : data{ other.data[0], other.data[1], other.data[2], other.data[3] } {}

			Vec4& operator[](int index) { return data[index]; }
			const Vec4& operator[](int index) const { return data[index]; }

			bool operator==(const Mat4& other) const
			{
				return data[0] == other.data[0] &&
					data[1] == other.data[1] &&
					data[2] == other.data[2] &&
					data[3] == other.data[3];
			}

			bool operator!=(const Mat4& other) const
			{
				return !(*this == other);
			}
		};
	}
}

#endif // MATH__MATH_DATA_TYPES__HPP
