#include "../include/Translatable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"


namespace Andromeda
{
	Translatable::Translatable()
		: m_stateChanged{ false }
		, m_position{ 0.0f }
		, m_translationMatrix{ 1.0f }
	{
	}

	Translatable::~Translatable() = default;

	bool Translatable::StateChanged() const
	{
		return m_stateChanged;
	}

	const Math::Vec3& Translatable::GetPosition() const
	{
		return m_position;
	}

	const Math::Mat4& Translatable::GetTranslationMatrix() const
	{
		m_translationMatrix;
	}

	void Translatable::ResetState()
	{
		m_stateChanged = false;
	}

	void Translatable::SetPosition(const Math::Vec3& position)
	{
		m_position = position;
		UpdateTranslationMatrix();
		m_stateChanged = true;
	}

	void Translatable::Translatable::Translate(const Math::Vec3& translation)
	{
		m_position += translation;
		UpdateTranslationMatrix();
		m_stateChanged = true;
	}

	void Translatable::UpdateTranslationMatrix()
	{
		m_translationMatrix = Math::LinAlgOps::Translate(m_translationMatrix, m_position);
	}
}