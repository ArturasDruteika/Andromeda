#ifndef SPACE__POINTS__HPP
#define SPACE__POINTS__HPP


namespace Andromeda
{
	namespace Space
	{
        struct Color
        {
            float r;
            float g;
            float b;
            float a;

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


#endif // SPACE__SPACE__HPP