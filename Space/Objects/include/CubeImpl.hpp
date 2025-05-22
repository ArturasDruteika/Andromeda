#ifndef SPACE__CUBE_IMPL__HPP
#define SPACE__CUBE_IMPL__HPP


#include "../include/Cube.hpp"


namespace Andromeda
{
	namespace Space
	{
		class Cube::CubeImpl
		{
		public:
			CubeImpl(const Math::Vec3& centerPosition, float halfExtent, const Color& color);
			~CubeImpl();

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
			double GetHalfExtent() const;

		private:
			float m_halfExtent;
			Math::Vec3 m_centerPosition;
			Color m_color;
			ObjectType m_type;
		};
	}
}


#endif // SPACE__CUBE_IMPL__HPP