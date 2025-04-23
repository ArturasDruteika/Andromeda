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
			ObjectBase();
			~ObjectBase();

			// Getters
			virtual ObjectType GetType() const = 0;
			virtual Math::Vec3 GetPosition() const = 0;
			virtual Color GetColor() const = 0;
			//Setters
			virtual void SetColor(const Color& color) = 0;
			virtual void SetPosition(const Math::Vec3& position) = 0;

			// TODO: implement these methods
			//void Move(const Math::Vec3& postion);
			//void Rotate(const Math::Vec3& rotation);
			//void Scale(const Math::Vec3& scale);
		};
	}
}


#endif // SPACE__OBJECT_BASE__HPP