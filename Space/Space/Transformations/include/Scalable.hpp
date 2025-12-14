#ifndef SPACE__TRANSFORMATIONS__SCALABLE__HPP
#define SPACE__TRANSFORMATIONS__SCALABLE__HPP


#include "Andromeda/Space/Transformations/IScalable.hpp"


namespace Andromeda
{
	class Scalable
		: public virtual IScalable
	{
	public:
		Scalable();
		~Scalable() override;

		// Getters
		bool StateChanged() const;
		const Math::Vec3& GetScale() const override;
		const Math::Mat4& GetScaleMatrix() const;
		// Setters
		void ResetState();
		void SetScale(const Math::Vec3& scale) override;

		void Scale(const Math::Vec3& scale) override;
		void Scale(float uniformScale) override;

	protected:
		void UpdateScaleMatrix();

	private:
		bool m_stateChanged;
		Math::Vec3 m_scale;
		Math::Mat4 m_scaleMatrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__SCALABLE__HPP