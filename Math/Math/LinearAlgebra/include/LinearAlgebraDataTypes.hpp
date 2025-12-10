#ifndef MATH__MATH_DATA_TYPES__HPP
#define MATH__MATH_DATA_TYPES__HPP


#include <array>


namespace Andromeda::Math
{
    struct Vec2
    {
        std::array<float, 2> data;

        constexpr Vec2()
            : data{ 0.0f, 0.0f }
        {
        }

        constexpr Vec2(float value)
            : data{ value, value }
        {
        }

        constexpr Vec2(float x, float y)
            : data{ x, y }
        {
        }

        constexpr Vec2(const Vec2& other)
            : data{ other.data[0], other.data[1] }
        {
        }

        float& operator[](int index)
        {
            return data[index];
        }

        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

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

        static constexpr int Size()
        {
            return sizeof(Vec2) / sizeof(float);
        }
    };

    struct Vec3
    {
        std::array<float, 3> data;

        constexpr Vec3()
            : data{ 0.0f, 0.0f, 0.0f }
        {
        }

        constexpr Vec3(float value)
            : data{ value, value, value }
        {
        }

        constexpr Vec3(float x, float y, float z)
            : data{ x, y, z }
        {
        }

        constexpr Vec3(const Vec3& other)
            : data{ other.data[0], other.data[1], other.data[2] }
        {
        }

        float& operator[](int index)
        {
            return data[index];
        }

        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

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

        static constexpr int Size()
        {
            return sizeof(Vec3) / sizeof(float);
        }
    };

    struct Vec4
    {
        std::array<float, 4> data;

        constexpr Vec4()
            : data{ 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        constexpr Vec4(float value)
            : data{ value, value, value, value }
        {
        }

        constexpr Vec4(float x, float y, float z, float w)
            : data{ x, y, z, w }
        {
        }

        constexpr Vec4(const Vec4& other)
            : data{ other.data[0], other.data[1], other.data[2], other.data[3] }
        {
        }

        float& operator[](int index)
        {
            return data[index];
        }

        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

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

        static constexpr int Size()
        {
            return sizeof(Vec4) / sizeof(float);
        }
    };

    struct Mat2
    {
        std::array<Vec2, 2> data;

        constexpr Mat2()
            : data{ Vec2(), Vec2() }
        {
        }

        constexpr Mat2(float value)
            : data{ Vec2(value), Vec2(value) }
        {
        }

        constexpr Mat2(const Vec2& row0, const Vec2& row1)
            : data{ row0, row1 }
        {
        }

        constexpr Mat2(const Mat2& other)
            : data{ other.data[0], other.data[1] }
        {
        }

        Vec2& operator[](int index)
        {
            return data[index];
        }

        constexpr const Vec2& operator[](int index) const
        {
            return data[index];
        }

        bool operator==(const Mat2& other) const
        {
            return data[0] == other.data[0] && data[1] == other.data[1];
        }

        bool operator!=(const Mat2& other) const
        {
            return !(*this == other);
        }

        static constexpr int Size()
        {
            return sizeof(Mat2) / sizeof(float);
        }
    };

    struct Mat3
    {
        std::array<Vec3, 3> data;

        constexpr Mat3()
            : data{ Vec3(), Vec3(), Vec3() }
        {
        }

        constexpr Mat3(float value)
            : data{ Vec3(value), Vec3(value), Vec3(value) }
        {
        }

        constexpr Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2)
            : data{ row0, row1, row2 }
        {
        }

        constexpr Mat3(const Mat3& other)
            : data{ other.data[0], other.data[1], other.data[2] }
        {
        }

        Vec3& operator[](int index)
        {
            return data[index];
        }

        constexpr const Vec3& operator[](int index) const
        {
            return data[index];
        }

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

        static constexpr int Size()
        {
            return sizeof(Mat3) / sizeof(float);
        }
    };

    struct Mat4
    {
        std::array<Vec4, 4> data;

        constexpr Mat4()
            : data{ Vec4(), Vec4(), Vec4(), Vec4() }
        {
        }

        constexpr Mat4(float value)
            : data{ Vec4(value), Vec4(value), Vec4(value), Vec4(value) }
        {
        }

        constexpr Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3)
            : data{ row0, row1, row2, row3 }
        {
        }

        constexpr Mat4(const Mat4& other)
            : data{ other.data[0], other.data[1], other.data[2], other.data[3] }
        {
        }

        Vec4& operator[](int index)
        {
            return data[index];
        }

        constexpr const Vec4& operator[](int index) const
        {
            return data[index];
        }

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

        static constexpr int Size()
        {
            return sizeof(Mat4) / sizeof(float);
        }
    };

    // ============================================================
    // VECTOR * SCALAR
    // ============================================================

    inline Vec2 operator*(const Vec2& v, float s)
    {
        return Vec2(v[0] * s, v[1] * s);
    }

    inline Vec3 operator*(const Vec3& v, float s)
    {
        return Vec3(v[0] * s, v[1] * s, v[2] * s);
    }

    inline Vec4 operator*(const Vec4& v, float s)
    {
        return Vec4(v[0] * s, v[1] * s, v[2] * s, v[3] * s);
    }

    inline Vec2 operator*(float s, const Vec2& v)
    {
        return v * s;
    }

    inline Vec3 operator*(float s, const Vec3& v)
    {
        return v * s;
    }

    inline Vec4 operator*(float s, const Vec4& v)
    {
        return v * s;
    }

    // ============================================================
    // MATRIX * VECTOR
    // ============================================================

    inline Vec2 operator*(const Mat2& m, const Vec2& v)
    {
        return Vec2(
            m[0][0] * v[0] + m[0][1] * v[1],
            m[1][0] * v[0] + m[1][1] * v[1]
        );
    }

    inline Vec3 operator*(const Mat3& m, const Vec3& v)
    {
        return Vec3(
            m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
            m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
            m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]
        );
    }

    inline Vec4 operator*(const Mat4& m, const Vec4& v)
    {
        return Vec4(
            m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
            m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
            m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
            m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
        );
    }

    // ============================================================
    // MATRIX * MATRIX
    // ============================================================

    inline Mat2 operator*(const Mat2& a, const Mat2& b)
    {
        Mat2 result;

        for (int r = 0; r < 2; ++r)
        {
            for (int c = 0; c < 2; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    inline Mat3 operator*(const Mat3& a, const Mat3& b)
    {
        Mat3 result;

        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c] +
                    a[r][2] * b[2][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    inline Mat4 operator*(const Mat4& a, const Mat4& b)
    {
        Mat4 result;

        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c] +
                    a[r][2] * b[2][c] +
                    a[r][3] * b[3][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    // ============================================================
    // MATRIX *= MATRIX
    // ============================================================

    inline Mat2& operator*=(Mat2& a, const Mat2& b)
    {
        a = a * b;
        return a;
    }

    inline Mat3& operator*=(Mat3& a, const Mat3& b)
    {
        a = a * b;
        return a;
    }

    inline Mat4& operator*=(Mat4& a, const Mat4& b)
    {
        a = a * b;
        return a;
    }

} // namespace Andromeda::Math

#endif // MATH__MATH_DATA_TYPES__HPP
