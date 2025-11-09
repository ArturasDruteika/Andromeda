#include "../include/SceneEnvironment.hpp"


namespace Andromeda::Rendering
{
	SceneEnvironment::SceneEnvironment()
		: m_gridSpacing(1.0f)
		, m_ambientStrength(0.1f)
		, m_backroundColor{ 0.0f, 0.0f, 0.0f, 1.0f }
	{
	}

	SceneEnvironment::~SceneEnvironment() = default;

	float SceneEnvironment::GetAmbientStrength() const
	{
		return m_ambientStrength;
	}

	const glm::vec4& SceneEnvironment::GetBackgroundColor() const
	{
		return m_backroundColor;
	}

	void SceneEnvironment::SetAmbientStrength(float ambientStrength)
	{
		m_ambientStrength = ambientStrength;
	}

	void SceneEnvironment::SetBackgroundColor(const glm::vec4& backroundColor)
	{
		m_backroundColor = backroundColor;
	}

	void SceneEnvironment::ResizeGrid(float resizeFactor)
	{
		if (resizeFactor > 0.0f)
		{
			m_gridSpacing *= resizeFactor;
		}
		else
		{
			throw std::invalid_argument("Resize factor must be greater than zero.");
		}
	}
}
