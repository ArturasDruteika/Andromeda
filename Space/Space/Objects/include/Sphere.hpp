#ifndef RENDERING__ABSTRACTS__TRANSFORMABLE__HPP
#define RENDERING__ABSTRACTS__TRANSFORMABLE__HPP


#include "Andromeda/Space/Colors/Colors.hpp"
#include "Andromeda/Space/Objects/ISphere.hpp"
#include "Space/Objects/include/GeometricObject.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
    class Sphere
        : public virtual ISphere
        , public GeometricObject
    {
    public:
        Sphere(float radius, const Math::Vec3& position, const Color& color);
        ~Sphere();

        // Getters
        float GetRadius() const;
		// Setters
        void SetRadius(float radius);

    private:
        void ConstructSphere(float radius, int sectorCount, int stackCount, const Color& color);
        void ValidateSphereParams(int& sectorCount, int& stackCount) const;
        void GenerateSphereVertices(
            float radius,
            int sectorCount,
            int stackCount,
            const Color& color,
            std::vector<Vertex>& outVertices
        ) const;

        void GenerateSphereIndices(
            int sectorCount,
            int stackCount,
            std::vector<unsigned int>& outIndices
        ) const;

        static Math::Vec3 ComputeSphereNormal(float x, float y, float z);

    private:
        float m_radius;
    };
}


#endif // RENDERING__ABSTRACTS__TRANSFORMABLE__HPP