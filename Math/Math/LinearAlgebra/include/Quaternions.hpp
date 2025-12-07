#ifndef MATH__LINEAR_ALGEBRA__QUATERNIONS__HPP
#define MATH__LINEAR_ALGEBRA__QUATERNIONS__HPP


namespace Andromeda::Math
{
    struct Vec3;

    class Quaternion
    {
    public:
        float w;
        float x;
        float y;
        float z;

        Quaternion();
        Quaternion(float w_, float x_, float y_, float z_);

        static Quaternion Identity();

        // Construction
        static Quaternion FromAxisAngle(const Vec3& axis, float angleRadians);

        // Basic ops
        static float Length(const Quaternion& q);
        static float LengthSquared(const Quaternion& q);

        static Quaternion Normalize(const Quaternion& q, float epsilon = 1e-6f);
        static Quaternion Conjugate(const Quaternion& q);
        static Quaternion Inverse(const Quaternion& q, float epsilon = 1e-6f);

        // Arithmetic
        static Quaternion Multiply(const Quaternion& a, const Quaternion& b);
        static Quaternion Add(const Quaternion& a, const Quaternion& b);
        static Quaternion Sub(const Quaternion& a, const Quaternion& b);

        // Dot
        static float Dot(const Quaternion& a, const Quaternion& b);

        // Slerp
        static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon = 1e-6f);

        // Rotate vector
        static Vec3 RotateVector(const Quaternion& q, const Vec3& v);
    };
}

#endif
