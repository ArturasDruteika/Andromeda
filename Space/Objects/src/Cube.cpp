#include "../include/Cube.hpp"
#include "../include/CubeImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Cube::Cube(const Math::Vec3& centerPosition, float halfExtent, const Color& color)
			: m_pCubeImpl{ new CubeImpl(centerPosition, halfExtent, color) }
		{
		}

		Cube::~Cube() = default;

		ObjectType Cube::GetType() const
		{
			return m_pCubeImpl->GetType();
		}

		Math::Vec3 Cube::GetCenterPosition() const
		{
			return m_pCubeImpl->GetCenterPosition();
		}

		Color Cube::GetColor() const
		{
			return m_pCubeImpl->GetColor();
		}

		void Cube::SetColor(const Color& color)
		{
			m_pCubeImpl->SetColor(color);
		}

		void Cube::SetCenterPosition(const Math::Vec3& position)
		{
			m_pCubeImpl->SetCenterPosition(position);
		}

		void Cube::RelativeMove(const Math::Vec3& position)
		{
		}

		void Cube::AbsoluteMove(const Math::Vec3& position)
		{
		}

		void Cube::Rotate(const Math::Vec3& rotation)
		{
		}

		void Cube::Scale(const Math::Vec3& scale)
		{
		}

		double Cube::GetHalfExtent() const
		{
			return m_pCubeImpl->GetHalfExtent();
		}
	}
}
