#include "../include/SphereImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Sphere::SphereImpl::SphereImpl(const Math::Vec3& position, const Color& color)
			: m_type{ ObjectType::SPHERE }
			, m_position{ position }
			, m_color{ color }
			, m_radius{ 0.0f }
		{
		}

		Sphere::SphereImpl::~SphereImpl() = default;

		ObjectType Sphere::SphereImpl::GetType() const
		{
			return m_type;
		}

		Math::Vec3 Sphere::SphereImpl::GetPosition() const
		{
			return m_position;
		}

		Color Sphere::SphereImpl::GetColor() const
		{
			return m_color;
		}

		void Sphere::SphereImpl::SetColor(const Color& color)
		{
			m_color = color;
		}

		void Sphere::SphereImpl::SetPosition(const Math::Vec3& position)
		{
			m_position = position;
		}

		double Sphere::SphereImpl::GetRadius() const
		{
			return m_radius;
		}
	}
}
