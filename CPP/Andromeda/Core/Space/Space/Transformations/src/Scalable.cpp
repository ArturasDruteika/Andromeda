#include "../include/Scalable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"


namespace Andromeda
{
	Scalable::Scalable()
		: m_stateChanged{ false}
		, m_scale{ 1.0f }
		, m_scaleMatrix{}
	{
	}

	Scalable::~Scalable() = default;

	bool Scalable::StateChanged() const
	{
		return m_stateChanged;
	}

	const Math::Vec3& Scalable::GetScale() const
	{
		return m_scale;
	}

	const Math::Mat4& Scalable::GetScaleMatrix() const
	{
		return m_scaleMatrix;
	}

	void Scalable::ResetState()
	{
		m_stateChanged = false;
	}

	void Scalable::SetScale(const Math::Vec3& scale)
	{
		m_scale = scale;
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::Scale(const Math::Vec3& scale)
	{
		m_scale += scale;
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::Scale(float uniformScale)
	{
		m_scale += Math::Vec3{ uniformScale };
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::UpdateScaleMatrix()
	{
		m_scaleMatrix = Math::LinAlgOps::Scale(m_scaleMatrix, m_scale);
	}
}