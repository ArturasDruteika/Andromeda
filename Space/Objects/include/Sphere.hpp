#ifndef SPACE__SPHERE__HPP
#define SPACE__SPHERE__HPP


#if defined(_WIN32)
	#if defined(SPACE_EXPORT)
		#define SPACE_API __declspec(dllexport)
	#else
		#define SPACE_API __declspec(dllimport)
	#endif /* SPACE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define SPACE_API __attribute__((visibility("default")))
#endif


#include "ObjectTypes.hpp"
#include "ObjectBase.hpp"
#include "../../Attributes/include/Colors.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Space
	{
		class SPACE_API Sphere : public ObjectBase
		{
		public:
			Sphere(const Math::Vec3& position, const Color& color);
			~Sphere();

			// Getters
			double GetRadius() const;

		private:
			float m_radius;

		};
	}
}


#endif // SPACE__SPHERE__HPP