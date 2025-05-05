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
			virtual Math::Vec3 GetCenterPosition() const = 0;
			virtual Color GetColor() const = 0;
			//Setters
			virtual void SetColor(const Color& color) = 0;
			virtual void SetCenterPosition(const Math::Vec3& position) = 0;

			virtual void RelativeMove(const Math::Vec3& postion) = 0;
			virtual void AbsoluteMove(const Math::Vec3& postion) = 0;
			virtual void Rotate(const Math::Vec3& rotation) = 0;
			virtual void Scale(const Math::Vec3& scale) = 0;
		};
	}
}


#endif // SPACE__OBJECT_BASE__HPP