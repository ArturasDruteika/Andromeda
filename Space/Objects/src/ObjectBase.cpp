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
	}
}
