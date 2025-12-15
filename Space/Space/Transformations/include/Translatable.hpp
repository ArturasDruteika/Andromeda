#ifndef SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP


#include "Andromeda/Space/Transformations/ITranslatable.hpp"


namespace Andromeda
{
	class Translatable
		: public virtual ITranslatable
	{
	public:
		Translatable();
		Translatable(const Math::Vec3& position);
		~Translatable() override;

		// Getters
		bool StateChanged() const;
		const Math::Vec3& GetPosition() const override;
		const Math::Mat4& GetTranslationMatrix() const override;
		// Setters
		void ResetState();
		void SetPosition(const Math::Vec3& position) override;

		void Translate(const Math::Vec3& translation) override;

	protected:
		void UpdateTranslationMatrix();

	private:
		bool m_stateChanged;
		Math::Vec3 m_position;
		Math::Mat4 m_translationMatrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP