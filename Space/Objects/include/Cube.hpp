#ifndef SPACE__CUBE__HPP
#define SPACE__CUBE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "ObjectTypes.hpp"
#include "ObjectBase.hpp"
#include "../../Attributes/include/Colors.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	namespace Space
	{
		class SPACE_API Cube : public ObjectBase
		{
		public:
			Cube(const Math::Vec3& centerPosition, float halfExtent, const Color& color);
			~Cube();

			// Overrides from ObjectBase
			// Getters
			ObjectType GetType() const override;
			Math::Vec3 GetCenterPosition() const override;
			Color GetColor() const override;
			//Setters
			void SetColor(const Color& color) override;
			void SetCenterPosition(const Math::Vec3& position) override;

			void RelativeMove(const Math::Vec3& position) override;
			void AbsoluteMove(const Math::Vec3& position) override;
			void Rotate(const Math::Vec3& rotation) override;
			void Scale(const Math::Vec3& scale) override;

			// Getters
			double GetHalfExtent() const;

		private:
			class CubeImpl;
			CubeImpl* m_pCubeImpl;
		};
	}
}


#endif // SPACE__CUBE__HPP