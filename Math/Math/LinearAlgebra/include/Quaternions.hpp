#ifndef MATH__LINEAR_ALGEBRA__QUATERNIONS__HPP
#define MATH__LINEAR_ALGEBRA__QUATERNIONS__HPP


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Math
{
    // Lightweight value type
    struct Quaternion
    {
        float w;
        float x;
        float y;
        float z;

        Quaternion()
            : w(1.0f)
            , x(0.0f)
            , y(0.0f)
            , z(0.0f)
        {
        }

        Quaternion(float w_, float x_, float y_, float z_)
            : w(w_)
            , x(x_)
            , y(y_)
            , z(z_)
        {
        }

        static Quaternion Identity()
        {
            return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
        }
    };

    // All operations live here and will be implemented with glm in the .cpp
    class QuaternionOps
    {
    public:
        // Construction
        static Quaternion Identity();
        static Quaternion FromAxisAngle(const Vec3& axis, float angleRadians);

        // Basic properties
        static float Length(const Quaternion& q);
        static float LengthSquared(const Quaternion& q);

        // Unary ops
        static Quaternion Normalize(const Quaternion& q, float epsilon = 1e-6f);
        static Quaternion Conjugate(const Quaternion& q);
        static Quaternion Inverse(const Quaternion& q, float epsilon = 1e-6f);

        // Arithmetic
        static Quaternion Multiply(const Quaternion& a, const Quaternion& b);
        static Quaternion Add(const Quaternion& a, const Quaternion& b);
        static Quaternion Sub(const Quaternion& a, const Quaternion& b);

        // Dot
        static float Dot(const Quaternion& a, const Quaternion& b);

        // Spherical linear interpolation, t in [0, 1]
        static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon = 1e-6f);

        // Rotate a vector by a quaternion (q * v * q^-1)
        static Vec3 RotateVector(const Quaternion& q, const Vec3& v);

		// Create a quaternion representing a rotation of angleRadians around axis
        static Quaternion AngleAxis(float angleRadians, const Vec3& axis);

		// Rotate vector v by quaternion q
        static Vec3 Rotate(const Quaternion& q, const Vec3& v);

        // Conversion
        static Quaternion FromEulerXYZ(float xRadians, float yRadians, float zRadians);
        static Vec3 ToEulerXYZ(const Quaternion& q);
        static Mat4 ToMat4(const Quaternion& q);
    };
}


#endif // MATH__LINEAR_ALGEBRA__QUATERNIONS__HPP
