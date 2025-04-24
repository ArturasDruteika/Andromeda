#include "../include/Sphere.hpp"
#include "../include/SphereImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Sphere::Sphere(const Math::Vec3& position, const Color& color)
			: m_pSphereImpl{ new SphereImpl(position, color) }
		{
		}

		Sphere::~Sphere() = default;

		ObjectType Sphere::GetType() const
		{
			return m_pSphereImpl->GetType();
		}

		Math::Vec3 Sphere::GetPosition() const
		{
			return m_pSphereImpl->GetPosition();
		}

		Color Sphere::GetColor() const
		{
			return m_pSphereImpl->GetColor();
		}

		void Sphere::SetColor(const Color& color)
		{
			m_pSphereImpl->SetColor(color);
		}

		void Sphere::SetPosition(const Math::Vec3& position)
		{
			m_pSphereImpl->SetPosition(position);
		}

		void Sphere::RelativeMove(const Math::Vec3& position)
		{
		}

		void Sphere::AbsoluteMove(const Math::Vec3& position)
		{
		}

		void Sphere::Rotate(const Math::Vec3& rotation)
		{
		}

		void Sphere::Scale(const Math::Vec3& scale)
		{
		}

		double Sphere::GetRadius() const
		{
			return m_pSphereImpl->GetRadius();
		}
	}
}
