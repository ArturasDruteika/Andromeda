#ifndef SPACE__OBJECTS__CUBE__HPP
#define SPACE__OBJECTS__CUBE__HPP


#include "GeometricObject.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Colors/Colors.hpp"
#include "Andromeda/Space/Objects/ICube.hpp"


namespace Andromeda::Space
{
    struct CubeFaceData
    {
        Math::Vec3 normal;
        std::array<Math::Vec3, 4> vertices;
    };

    class Cube
        : public virtual ICube
        , public GeometricObject
    {
    public:
        Cube(float halfExtent, const Math::Vec3& position, const Color& color);
        ~Cube();

		// Getters
		float GetHalfExtent() const;
		// Setters
		void SetHalfExtent(float halfExtent);
    
    private:
        void ConstructCube(float halfExtent, const Color& color);
        static std::array<CubeFaceData, 6> BuildCubeFaces(float halfExtent);
        static void ReserveCubeBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
        static void AppendFace(
            const CubeFaceData& face,
            const Color& color,
            std::vector<Vertex>& outVertices,
            std::vector<unsigned int>& outIndices,
            unsigned int& indexOffset
        );

    private:
		float m_halfExtent;

    };
}


#endif // SPACE__OBJECTS__CUBE__HPP