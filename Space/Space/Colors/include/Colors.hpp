#ifndef SPACE__COLORS__HPP
#define SPACE__COLORS__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
    // TODO: consider using Math::Vec4 vector to store data for speed
    struct Color
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;

        static constexpr int Size()
        {
            return sizeof(Color) / sizeof(float);
        }

        bool operator==(const Color& other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

		Math::Vec4 ReturnAsVec4() const
		{
            return { r, g, b, a };
		}
    };
}


#endif // SPACE__COLORS__HPP