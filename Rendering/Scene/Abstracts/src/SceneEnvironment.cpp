#include "../include/SceneEnvironment.hpp"


namespace Andromeda::Rendering
{
	SceneEnvironment::SceneEnvironment()
		: m_gridSpacing(1.0f)
		, m_ambientStrength(0.1f)
	{
	}

	SceneEnvironment::~SceneEnvironment() = default;

	float SceneEnvironment::GetAmbientStrength() const
	{
		return m_ambientStrength;
	}

	void SceneEnvironment::SetAmbientStrength(float ambientStrength)
	{
		m_ambientStrength = ambientStrength;
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
