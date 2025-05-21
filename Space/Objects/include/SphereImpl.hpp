#ifndef SPACE__SPHERE_IMPL__HPP
#define SPACE__SPHERE_IMPL__HPP


#include "../include/Sphere.hpp"


namespace Andromeda
{
	namespace Space
	{
		class Sphere::SphereImpl
		{
		public:
			SphereImpl(const Math::Vec3& centerPosition, float radius, const Color& color);
			~SphereImpl();

			// Getters
			ObjectType GetType() const;
			Math::Vec3 GetCenterPosition() const;
			Color GetColor() const;
			//Setters
			void SetColor(const Color& color);
			void SetCenterPosition(const Math::Vec3& position);

			void RelativeMove(const Math::Vec3& position);
			void AbsoluteMove(const Math::Vec3& position);
			void Rotate(const Math::Vec3& rotation);
			void Scale(const Math::Vec3& scale);

			// Getters
			double GetRadius() const;

		private:
			float m_radius;
			Math::Vec3 m_centerPosition;
			Color m_color;
			ObjectType m_type;
		};
	}
}


#endif // SPACE__SPHERE_IMPL__HPP