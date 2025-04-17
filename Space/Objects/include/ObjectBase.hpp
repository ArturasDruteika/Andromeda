#ifndef SPACE__OBJECT_BASE__HPP
#define SPACE__OBJECT_BASE__HPP


#include "../include/ObjectTypes.hpp"


namespace Andromeda
{
	namespace Space
	{
		class ObjectBase
		{
		public:
			ObjectBase(const ObjectType& objType);
			~ObjectBase();

			// Getters
			ObjectType GetType() const;

		private:
			ObjectType m_type;
		};
	}
}


#endif // SPACE__OBJECT_BASE__HPP