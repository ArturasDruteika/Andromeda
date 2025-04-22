#include "../include/Sphere.hpp"


namespace Andromeda
{
	namespace Space
	{
		Sphere::Sphere()
			: ObjectBase(ObjectType::Sphere)
			, m_radius(0.0f)
		{
		}

		Sphere::~Sphere() = default;

		double Sphere::GetRadius() const
		{
			return m_radius;
		}
	}
}
