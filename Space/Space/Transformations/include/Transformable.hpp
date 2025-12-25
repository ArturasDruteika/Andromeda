#ifndef SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP


#include "Rotatable.hpp"
#include "Scalable.hpp"
#include "Translatable.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Transformations/ITransformable.hpp"


namespace Andromeda
{
	class SPACE_API Transformable
		: public virtual ITransformable
		, public Rotatable
		, public Scalable
		, public Translatable
	{
	public:
		Transformable();
		Transformable(const Math::Vec3& position);
		~Transformable() override;

		// Getters
		bool StateChanged() const override;
		Math::Mat4 GetModelMatrix() override;
		// Setters
		void SetModelMatrix(const Math::Mat4& modelMatrix) override;

		void ResetState() override;

	private:
		bool m_stateChanged;
		Math::Mat4 m_modelMatrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP