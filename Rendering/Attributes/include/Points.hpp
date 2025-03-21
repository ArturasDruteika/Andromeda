#ifndef ENVIRONMENT__COLORS__HPP
#define ENVIRONMENT__COLORS__HPP


namespace Andromeda
{
	namespace Rendering
	{
		struct Point3D
		{
			float x;
			float y;
			float z;

			static constexpr int Size()
			{
				return sizeof(Point3D) / sizeof(float);
			}
		};
	}
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP