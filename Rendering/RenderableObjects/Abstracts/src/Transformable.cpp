#include "../include/Transformable.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	Transformable::Transformable(const Math::Vec3& centerPosition)
		: m_stateChanged{ false }
		, m_centerPosition{ MathUtils::ToGLM(centerPosition) }
		, m_rotation{ 0.0f, 0.0f, 0.0f }
		, m_scale{ 1.0f, 1.0f, 1.0f }
		, m_translationMatrix{ glm::mat4(1.0f) }
		, m_rotationMatrix{ glm::mat4(1.0f) }
		, m_scaleMatrix{ glm::mat4(1.0f) }
		, m_modelMatrix{ glm::mat4(1.0f) }
	{
	}

	Transformable::~Transformable() = default;

	bool Transformable::StateChanged() const
	{
		return m_stateChanged;
	}

	Math::Vec3 Transformable::GetCenterPosition() const
	{
		return MathUtils::FromGLM(m_centerPosition);
	}

	Math::Mat4 Transformable::GetModelMatrix() const
	{
		return MathUtils::FromGLM(m_modelMatrix);
	}

	void Transformable::ResetState()
	{
		m_stateChanged = false;
	}

	void Transformable::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_modelMatrix = MathUtils::ToGLM(modelMatrix);
	}

	void Transformable::Translate(const Math::Vec3& translation)
	{
		m_centerPosition = MathUtils::ToGLM(translation);
		UpdateModelMatrix(TransformationType::TRANSLATE);
	}

	void Transformable::TranslateDelta(const Math::Vec3& translationDelta)
	{
		m_centerPosition += MathUtils::ToGLM(translationDelta);
		UpdateModelMatrix(TransformationType::TRANSLATE);
	}

	void Transformable::Rotate(const Math::Vec3& rotation)
	{
		m_rotation += MathUtils::ToGLM(rotation);
		UpdateModelMatrix(TransformationType::ROTATE);
	}

	void Transformable::RotateX(float angle)
	{
		m_rotation += glm::vec3(angle, 0.0f, 0.0f);
		UpdateModelMatrix(TransformationType::ROTATE);
	}

	void Transformable::RotateY(float angle)
	{
		m_rotation += glm::vec3(0.0f, angle, 0.0f);
		UpdateModelMatrix(TransformationType::ROTATE);
	}

	void Transformable::RotateZ(float angle)
	{
		m_rotation += glm::vec3(0.0f, 0.0f, angle);
		UpdateModelMatrix(TransformationType::ROTATE);
	}

	void Transformable::Scale(const Math::Vec3& scale)
	{
		m_scale += MathUtils::ToGLM(scale);
		UpdateModelMatrix(TransformationType::SCALE);
	}

	void Transformable::UpdateModelMatrix(const TransformationType& transformationType)
	{
		switch (transformationType)
		{
		case TransformationType::TRANSLATE:
		{
			m_translationMatrix = ConstructTranslationMatrix();
			break;
		}
		case TransformationType::ROTATE:
		{
			m_rotationMatrix = ConstructRotationMatrix();
			break;
		}
		case TransformationType::SCALE:
		{
			m_scaleMatrix = ConstructScaleMatrix();
			break;
		}
		case TransformationType::ALL:
		{
			m_translationMatrix = ConstructTranslationMatrix();
			m_rotationMatrix = ConstructRotationMatrix();
			m_scaleMatrix = ConstructScaleMatrix();
			break;
		}
		default:
		{
			spdlog::error("Invalid transformation type");
			break;
		}
		}

		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
		m_stateChanged = true;
	}

	glm::mat4 Transformable::ConstructTranslationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_centerPosition);
	}

	glm::mat4 Transformable::ConstructRotationMatrix() const
	{
		return glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * // Z rotation
			glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * // Y rotation
			glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X rotation;
	}

	glm::mat4 Transformable::ConstructScaleMatrix() const
	{
		return glm::scale(glm::mat4(1.0f), m_scale);
	}
}
