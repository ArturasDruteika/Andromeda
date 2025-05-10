#ifndef SPACE__COLORS__HPP
#define SPACE__COLORS__HPP


namespace Andromeda
{
	namespace Space
	{
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
        };

	}
}


#endif // SPACE__COLORS__HPP