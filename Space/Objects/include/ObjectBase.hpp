#ifndef SPACE__OBJECT_BASE__HPP
#define SPACE__OBJECT_BASE__HPP


#include "ObjectTypes.hpp"
#include "../../Attributes/include/Colors.hpp"


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
			Color GetColor() const;
			//Setters
			void SetColor(const Color& color);

		private:
			ObjectType m_type;
			Color m_color;

		};
	}
}


#endif // SPACE__OBJECT_BASE__HPP