#include "../include/Quaternions.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>


namespace Andromeda::Math
{
    namespace
    {
        inline glm::quat ToGlm(const Quaternion& q)
        {
            return glm::quat(q.w, q.x, q.y, q.z);
        }

        inline Quaternion FromGlm(const glm::quat& gq)
        {
            return Quaternion(gq.w, gq.x, gq.y, gq.z);
        }

        inline glm::vec3 ToGlm(const Vec3& v)
        {
            return glm::vec3(v.data[0], v.data[1], v.data[2]);
        }

        inline Vec3 FromGlm(const glm::vec3& gv)
        {
            return Vec3(gv.x, gv.y, gv.z);
        }

        inline glm::mat4 ToGlm(const Mat4& m)
        {
            glm::mat4 gm(1.0f);
            for (int c = 0; c < 4; ++c)
            {
                for (int r = 0; r < 4; ++r)
                {
                    gm[c][r] = m[c][r];
                }
            }
            return gm;
        }

        inline Mat4 FromGlm(const glm::mat4& gm)
        {
            Mat4 m(1.0f);
            for (int c = 0; c < 4; ++c)
            {
                for (int r = 0; r < 4; ++r)
                {
                    m[c][r] = gm[c][r];
                }
            }
            return m;
        }
    }

    Quaternion QuaternionOps::Identity()
    {
        return Quaternion::Identity();
    }

    Quaternion QuaternionOps::FromAxisAngle(const Vec3& axis, float angleRadians)
    {
        glm::vec3 gAxis = ToGlm(axis);
        glm::quat gq = glm::angleAxis(angleRadians, glm::normalize(gAxis));
        return FromGlm(gq);
    }

    float QuaternionOps::Length(const Quaternion& q)
    {
        return std::sqrt(LengthSquared(q));
    }

    float QuaternionOps::LengthSquared(const Quaternion& q)
    {
        return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
    }

    Quaternion QuaternionOps::Normalize(const Quaternion& q, float epsilon)
    {
        glm::quat g = ToGlm(q);
        float lenSq = glm::dot(g, g);

        if (lenSq <= epsilon * epsilon)
        {
            return q;
        }

        g = glm::normalize(g);
        return FromGlm(g);
    }

    Quaternion QuaternionOps::Conjugate(const Quaternion& q)
    {
        return Quaternion(q.w, -q.x, -q.y, -q.z);
    }

    Quaternion QuaternionOps::Inverse(const Quaternion& q, float epsilon)
    {
        glm::quat g = ToGlm(q);
        float lenSq = glm::dot(g, g);

        if (lenSq <= epsilon * epsilon)
        {
            return Identity();
        }

        g = glm::inverse(g);
        return FromGlm(g);
    }

    Quaternion QuaternionOps::Multiply(const Quaternion& a, const Quaternion& b)
    {
        glm::quat ga = ToGlm(a);
        glm::quat gb = ToGlm(b);
        glm::quat gr = ga * gb;
        return FromGlm(gr);
    }

    Quaternion QuaternionOps::Add(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w + b.w,
            a.x + b.x,
            a.y + b.y,
            a.z + b.z);
    }

    Quaternion QuaternionOps::Sub(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w - b.w,
            a.x - b.x,
            a.y - b.y,
            a.z - b.z);
    }

    float QuaternionOps::Dot(const Quaternion& a, const Quaternion& b)
    {
        return a.w * b.w +
            a.x * b.x +
            a.y * b.y +
            a.z * b.z;
    }

    Quaternion QuaternionOps::Slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon)
    {
        if (t <= 0.0f)
        {
            return a;
        }
        if (t >= 1.0f)
        {
            return b;
        }

        glm::quat ga = ToGlm(a);
        glm::quat gb = ToGlm(b);

        glm::quat gRes = glm::slerp(ga, gb, t);

        float lenSq = glm::dot(gRes, gRes);
        if (lenSq <= epsilon * epsilon)
        {
            gRes = glm::normalize(gRes);
        }

        return FromGlm(gRes);
    }

    Vec3 QuaternionOps::RotateVector(const Quaternion& q, const Vec3& v)
    {
        glm::quat gq = ToGlm(q);
        glm::vec3 gv = ToGlm(v);
        glm::vec3 gvRot = glm::rotate(gq, gv);
        return FromGlm(gvRot);
    }

    Quaternion QuaternionOps::AngleAxis(float angleRadians, const Vec3& axis)
    {
        return FromAxisAngle(axis, angleRadians);
    }

    Vec3 QuaternionOps::Rotate(const Quaternion& q, const Vec3& v)
    {
        return RotateVector(q, v);
    }

    Quaternion QuaternionOps::FromEulerXYZ(float xRadians, float yRadians, float zRadians)
    {
        // Build rotation matrix from Euler XYZ, then convert to quaternion.
        glm::mat4 R = glm::eulerAngleXYZ(xRadians, yRadians, zRadians);
        glm::quat q = glm::quat_cast(R);
        return FromGlm(q);
    }

    Vec3 QuaternionOps::ToEulerXYZ(const Quaternion& q)
    {
        glm::quat gq = ToGlm(q);

        // glm::eulerAngles returns a vec3 of Euler angles (in radians).
        // Interpretation corresponds to the chosen extraction convention.
        glm::vec3 e = glm::eulerAngles(gq);
        return FromGlm(e);
    }

    Mat4 QuaternionOps::ToMat4(const Quaternion& q)
    {
        glm::quat gq = ToGlm(q);
        glm::mat4 gm = glm::toMat4(gq);
        return FromGlm(gm);
    }
}
