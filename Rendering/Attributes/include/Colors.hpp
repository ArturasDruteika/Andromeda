#ifndef ENVIRONMENT__POINTS__HPP
#define ENVIRONMENT__POINTS__HPP


namespace Andromeda
{
	namespace Rendering
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
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP