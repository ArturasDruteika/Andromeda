#include "../include/Transformable.hpp"


namespace Andromeda
{
	Transformable::Transformable()
		: m_stateChanged{ false }
		, m_modelMatrix{ 1.0f }
	{
	}

	Transformable::Transformable(const Math::Vec3& position)
		: Translatable{ position }
		, m_stateChanged{ false }
		, m_modelMatrix{ 1.0f }
	{
	}

	Transformable::~Transformable() = default;

	bool Transformable::StateChanged() const
	{
		bool stateChanged = 
			m_stateChanged 
			|| Rotatable::StateChanged() 
			|| Scalable::StateChanged() 
			|| Translatable::StateChanged();
		return m_stateChanged;
	}

	Math::Mat4 Transformable::GetModelMatrix()
	{
		if (StateChanged())
		{
			m_modelMatrix = Translatable::GetTranslationMatrix() * Rotatable::GetRotationMatrix() * Scalable::GetScaleMatrix();
			m_stateChanged = false;
		}
		return m_modelMatrix;
	}

	void Transformable::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_modelMatrix = modelMatrix;
		m_stateChanged = true;
	}

	void Transformable::ResetState()
	{
		m_stateChanged = false;
		Rotatable::ResetState();
		Scalable::ResetState();
		Translatable::ResetState();
	}
}