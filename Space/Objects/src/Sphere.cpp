#include "../include/Sphere.hpp"


namespace Andromeda
{
	namespace Space
	{
		Sphere::Sphere(const Math::Vec3& position, const Color& color)
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
