#ifndef ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP
#define ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP


#include "GeometricObject.hpp"
#include "SurfaceObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Andromeda/Space/Objects/ISkyroom.hpp"
#include "Andromeda/Space/Colors/Colors.hpp"
#include "pch.hpp"


namespace Andromeda::Space
{
    struct SkyroomFaceData
    {
        Math::Vec3 normal;
        std::array<Math::Vec3, 4> vertices;
    };

    class SPACE_API Skyroom
		: public virtual ISkyroom
        , public GeometricObject
		, public SurfaceObject
    {
    public:
        Skyroom(float halfExtent, const Math::Vec3& position, const Color& color);
        ~Skyroom();

		// Getters
        float GetHalfExtent() const override;
		// Setters
        void SetHalfExtent(float halfExtent) override;

    private:
        void ConstructSkyroom(float halfExtent, const Color& color);
        void ValidateSkyroomParams(float halfExtent) const;

        static std::array<SkyroomFaceData, 6> BuildSkyroomFaces(float halfExtent);
        static void ReserveSkyroomBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

        static void AppendFaceInside(
            const SkyroomFaceData& face,
            const Color& color,
            std::vector<Vertex>& outVertices,
            std::vector<unsigned int>& outIndices,
            unsigned int& indexOffset
        );

    private:
        float m_halfExtent;
    };
}


#endif // ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP