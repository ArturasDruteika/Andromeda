#include "../include/Quaternions.hpp"
#include "../include/LinearAlgebraDataTypes.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cmath>


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
    }

    Quaternion::Quaternion()
        : w(1.0f)
        , x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

    Quaternion::Quaternion(float w_, float x_, float y_, float z_)
        : w(w_)
        , x(x_)
        , y(y_)
        , z(z_)
    {
    }

    Quaternion Quaternion::Identity()
    {
        return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }

    Quaternion Quaternion::FromAxisAngle(const Vec3& axis, float angleRadians)
    {
        glm::vec3 gAxis = ToGlm(axis);
        glm::quat gq = glm::angleAxis(angleRadians, glm::normalize(gAxis));
        return FromGlm(gq);
    }

    float Quaternion::Length(const Quaternion& q)
    {
        return std::sqrt(LengthSquared(q));
    }

    float Quaternion::LengthSquared(const Quaternion& q)
    {
        return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
    }

    Quaternion Quaternion::Normalize(const Quaternion& q, float epsilon)
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

    Quaternion Quaternion::Conjugate(const Quaternion& q)
    {
        return Quaternion(q.w, -q.x, -q.y, -q.z);
    }

    Quaternion Quaternion::Inverse(const Quaternion& q, float epsilon)
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

    Quaternion Quaternion::Multiply(const Quaternion& a, const Quaternion& b)
    {
        glm::quat ga = ToGlm(a);
        glm::quat gb = ToGlm(b);
        return FromGlm(ga * gb);
    }

    Quaternion Quaternion::Add(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
    }

    Quaternion Quaternion::Sub(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
    }

    float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
    {
        return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon)
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

    Vec3 Quaternion::RotateVector(const Quaternion& q, const Vec3& v)
    {
        glm::quat gq = ToGlm(q);
        glm::vec3 gv = ToGlm(v);
        glm::vec3 gvRot = glm::rotate(gq, gv);
        return FromGlm(gvRot);
    }
}
