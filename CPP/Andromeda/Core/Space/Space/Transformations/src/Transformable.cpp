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
	{
		UpdateModelMatrix();
	}

	Transformable::~Transformable() = default;

	bool Transformable::StateChanged() const
	{
		bool stateChanged = 
			m_stateChanged 
			|| Rotatable::StateChanged() 
			|| Scalable::StateChanged() 
			|| Translatable::StateChanged();
		return stateChanged;
	}

	Math::Mat4 Transformable::GetModelMatrix()
	{
		if (StateChanged())
		{
			UpdateModelMatrix();
			// Clear all dirty flags so subsequent calls do not rebuild again.
			m_stateChanged = false;
			Rotatable::ResetState();
			Scalable::ResetState();
			Translatable::ResetState();
		}
		return m_modelMatrix;
	}

	void Transformable::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_modelMatrix = modelMatrix;
		m_stateChanged = true;
	}

	void Transformable::UpdateModelMatrix()
	{
		// Rebuild model matrix from current component matrices.
		// Order matches your existing GetModelMatrix(): T * R * S
		m_modelMatrix =
			Translatable::GetTranslationMatrix()
			* Rotatable::GetRotationMatrix()
			* Scalable::GetScaleMatrix();
	}

	void Transformable::ResetState()
	{
		m_stateChanged = false;
		Rotatable::ResetState();
		Scalable::ResetState();
		Translatable::ResetState();
	}
}