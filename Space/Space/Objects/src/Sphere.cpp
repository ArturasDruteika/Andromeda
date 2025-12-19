#include "../include/Sphere.hpp"
#include "Math/Constants/include/Constants.hpp"
#include "pch.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Space
{
	Sphere::Sphere(float radius, const Math::Vec3& position, const Color& color)
		: GeometricObject{ position, color }
		, m_radius{ radius }
	{
        ConstructSphere(m_radius, 36, 18, color);
	}

	Sphere::~Sphere()
	{
	}

	float Sphere::GetRadius() const
	{
		return m_radius;
	}

	void Sphere::SetRadius(float radius)
	{
        if (radius <= 0.0f)
        {
            spdlog::error("Sphere radius must be greater than zero. Given radius: {}", radius);
            return;
        }

        m_radius = radius;
        ConstructSphere(m_radius, 36, 18, m_color);
	}

    void Sphere::ConstructSphere(float radius, int sectorCount, int stackCount, const Color& color)
    {
        ValidateSphereParams(sectorCount, stackCount);

        if (radius <= 0.0f)
        {
			spdlog::error("Sphere radius must be greater than zero. Given radius: {}", radius);
            return;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        vertices.reserve(static_cast<size_t>((stackCount + 1) * (sectorCount + 1)));
        indices.reserve(static_cast<size_t>(stackCount * sectorCount * 6));

        GenerateSphereVertices(radius, sectorCount, stackCount, color, vertices);
        GenerateSphereIndices(sectorCount, stackCount, indices);

        Mesh mesh;
        mesh.SetData(vertices, indices);

        SetMesh(mesh);
    }

    void Sphere::ValidateSphereParams(int& sectorCount, int& stackCount) const
    {
        if (sectorCount < 3)
        {
            sectorCount = 3;
        }

        if (stackCount < 2)
        {
            stackCount = 2;
        }
    }

    void Sphere::GenerateSphereVertices(
        float radius,
        int sectorCount,
        int stackCount,
        const Color& color,
        std::vector<Vertex>& outVertices
    ) const
    {
        const float sectorStep = 2.0f * Math::PI / static_cast<float>(sectorCount);
        const float stackStep = Math::PI / static_cast<float>(stackCount);

        for (int i = 0; i <= stackCount; ++i)
        {
            const float stackAngle = (Math::PI / 2.0f) - (static_cast<float>(i) * stackStep);
            const float xy = radius * std::cos(stackAngle);
            const float z = radius * std::sin(stackAngle);

            for (int j = 0; j <= sectorCount; ++j)
            {
                const float sectorAngle = static_cast<float>(j) * sectorStep;

                const float x = xy * std::cos(sectorAngle);
                const float y = xy * std::sin(sectorAngle);

                const Math::Vec3 normal = ComputeSphereNormal(x, y, z);

                outVertices.emplace_back(
                    Math::Vec3(x, y, z),
                    color,
                    normal
                );
            }
        }
    }

    void Sphere::GenerateSphereIndices(
        int sectorCount,
        int stackCount,
        std::vector<unsigned int>& outIndices
    ) const
    {
        for (int i = 0; i < stackCount; ++i)
        {
            int k1 = i * (sectorCount + 1);
            int k2 = k1 + (sectorCount + 1);

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                if (i != 0)
                {
                    outIndices.push_back(static_cast<unsigned int>(k1));
                    outIndices.push_back(static_cast<unsigned int>(k2));
                    outIndices.push_back(static_cast<unsigned int>(k1 + 1));
                }

                if (i != (stackCount - 1))
                {
                    outIndices.push_back(static_cast<unsigned int>(k1 + 1));
                    outIndices.push_back(static_cast<unsigned int>(k2));
                    outIndices.push_back(static_cast<unsigned int>(k2 + 1));
                }
            }
        }
    }

    Math::Vec3 Sphere::ComputeSphereNormal(float x, float y, float z)
    {
        const float lenSq = (x * x) + (y * y) + (z * z);

        if (lenSq <= 0.0f)
        {
            return Math::Vec3(0.0f, 0.0f, 0.0f);
        }

        const float invLen = 1.0f / std::sqrt(lenSq);
        return Math::Vec3(x * invLen, y * invLen, z * invLen);
    }
}

