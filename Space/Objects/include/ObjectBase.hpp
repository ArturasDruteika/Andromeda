#ifndef SPACE__OBJECT_BASE__HPP
#define SPACE__OBJECT_BASE__HPP


#include "ObjectTypes.hpp"
#include "../../Attributes/include/Colors.hpp"
#include "LinearAlgebraDataTypes.hpp"



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
			Math::Vec3 GetPosition() const;
			Color GetColor() const;
			//Setters
			void SetColor(const Color& color);
			void SetPosition(const Math::Vec3& position);

		private:
			ObjectType m_type;
			Math::Vec3 m_position;
			Color m_color;

		};
	}
}


#endif // SPACE__OBJECT_BASE__HPP