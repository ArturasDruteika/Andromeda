#include "../include/CubeImpl.hpp"


namespace Andromeda
{
	namespace Space
	{
		Cube::CubeImpl::CubeImpl(const Math::Vec3& centerPosition, float halfExtent, const Color& color)
			: m_type{ ObjectType::CUBE }
			, m_centerPosition{ centerPosition }
			, m_color{ color }
			, m_halfExtent{ halfExtent }
		{
		}

		Cube::CubeImpl::~CubeImpl() = default;

		ObjectType Cube::CubeImpl::GetType() const
		{
			return m_type;
		}

		Math::Vec3 Cube::CubeImpl::GetCenterPosition() const
		{
			return m_centerPosition;
		}

		Color Cube::CubeImpl::GetColor() const
		{
			return m_color;
		}

		void Cube::CubeImpl::SetColor(const Color& color)
		{
			m_color = color;
		}

		void Cube::CubeImpl::SetCenterPosition(const Math::Vec3& position)
		{
			m_centerPosition = position;
		}

		void Cube::CubeImpl::RelativeMove(const Math::Vec3& position)
		{
			m_centerPosition += position;
		}

		void Cube::CubeImpl::AbsoluteMove(const Math::Vec3& position)
		{
			m_centerPosition = position;
		}

		void Cube::CubeImpl::Rotate(const Math::Vec3& rotation)
		{
			// Implement rotation logic here
		}

		void Cube::CubeImpl::Scale(const Math::Vec3& scale)
		{
			// Implement scaling logic here
		}

		double Cube::CubeImpl::GetHalfExtent() const
		{
			return m_halfExtent;
		}
	}
}
