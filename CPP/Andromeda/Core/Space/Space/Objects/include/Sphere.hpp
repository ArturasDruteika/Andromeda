#ifndef ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP
#define ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP


#include "GeometricObject.hpp"
#include "SurfaceObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Colors/Colors.hpp"
#include "Andromeda/Space/Objects/ISphere.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
    class SPACE_API Sphere
        : public ISphere
        , public GeometricObject
		, public SurfaceObject
    {
    public:
        Sphere(float radius, const Color& color);
        ~Sphere();

        // Getters
        float GetRadius() const override;
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


#endif // ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP