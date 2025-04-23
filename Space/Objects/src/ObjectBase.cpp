#include "../include/ObjectBase.hpp"


namespace Andromeda
{
	namespace Space
	{
		ObjectBase::ObjectBase(const ObjectType& objType)
			: m_type(objType)
			, m_position{ 0.0f, 0.0f, 0.0f}
			, m_color{ 1.0f, 1.0f, 1.0f, 1.0f } // Default color is white
		{
		}

		ObjectBase::~ObjectBase() = default;

		ObjectType ObjectBase::GetType() const
		{
			return m_type;
		}

		Math::Vec3 ObjectBase::GetPosition() const
		{
			return m_position;
		}

		Color ObjectBase::GetColor() const
		{
			return m_color;
		}

		void ObjectBase::SetColor(const Color& color)
		{
			m_color = color;
		}

		void ObjectBase::SetPosition(const Math::Vec3& position)
		{
			m_position = position;
		}
	}
}
