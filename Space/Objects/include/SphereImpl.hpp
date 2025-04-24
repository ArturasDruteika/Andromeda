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
			SphereImpl(const Math::Vec3& position, const Color& color);
			~SphereImpl();

			/// Overrides from ObjectBase
			// Getters
			ObjectType GetType() const;
			Math::Vec3 GetPosition() const;
			Color GetColor() const;
			//Setters
			void SetColor(const Color& color);
			void SetPosition(const Math::Vec3& position);

			void RelativeMove(const Math::Vec3& position);
			void AbsoluteMove(const Math::Vec3& position);
			void Rotate(const Math::Vec3& rotation);
			void Scale(const Math::Vec3& scale);

			// Getters
			double GetRadius() const;

		private:
			ObjectType m_type;
			Math::Vec3 m_position;
			Color m_color;
			float m_radius;

		};
	}
}


#endif // SPACE__SPHERE_IMPL__HPP