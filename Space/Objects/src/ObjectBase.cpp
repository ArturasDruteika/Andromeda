#include "../include/ObjectBase.hpp"


namespace Andromeda
{
	namespace Space
	{
		ObjectBase::ObjectBase(const ObjectType& objType)
			: m_type(objType)
		{
		}

		ObjectBase::~ObjectBase() = default;

		ObjectType ObjectBase::GetType() const
		{
			return m_type;
		}

		Color ObjectBase::GetColor() const
		{
			return m_color;
		}

		void ObjectBase::SetColor(const Color& color)
		{
			m_color = color;
		}
	}
}
