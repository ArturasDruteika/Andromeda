#include "../include/SphereImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Sphere::SphereImpl::SphereImpl(const Math::Vec3& centerPosition, float radius, const Color& color)
			: m_type{ ObjectType::SPHERE }
			, m_centerPosition{ centerPosition }
			, m_color{ color }
			, m_radius{ radius }
		{
		}

		Sphere::SphereImpl::~SphereImpl() = default;

		ObjectType Sphere::SphereImpl::GetType() const
		{
			return m_type;
		}

		Math::Vec3 Sphere::SphereImpl::GetCenterPosition() const
		{
			return m_centerPosition;
		}

		Color Sphere::SphereImpl::GetColor() const
		{
			return m_color;
		}

		void Sphere::SphereImpl::SetColor(const Color& color)
		{
			m_color = color;
		}

		void Sphere::SphereImpl::SetCenterPosition(const Math::Vec3& position)
		{
			m_centerPosition = position;
		}

		void Sphere::SphereImpl::RelativeMove(const Math::Vec3& position)
		{
			m_centerPosition += position;
		}

		void Sphere::SphereImpl::AbsoluteMove(const Math::Vec3& position)
		{
			m_centerPosition = position;
		}

		void Sphere::SphereImpl::Rotate(const Math::Vec3& rotation)
		{
			// Implement rotation logic here
		}

		void Sphere::SphereImpl::Scale(const Math::Vec3& scale)
		{
			// Implement scaling logic here
		}

		double Sphere::SphereImpl::GetRadius() const
		{
			return m_radius;
		}
	}
}
