#include "../include/SceneEnvironment.hpp"


namespace Andromeda::Space
{
	SceneEnvironment::SceneEnvironment()
		: m_ambientStrength{ 0.1f }
		, m_backgroundColor{ Math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f } }
	{
	}

	SceneEnvironment::~SceneEnvironment() = default;

	float SceneEnvironment::GetAmbientStrength() const
	{
		return m_ambientStrength;
	}

	const Math::Vec4& SceneEnvironment::GetBackgroundColor() const
	{
		return m_backgroundColor;
	}

	void SceneEnvironment::SetAmbientStrength(float ambientStrength)
	{
		m_ambientStrength = ambientStrength;
	}

	void SceneEnvironment::SetBackgroundColor(const Math::Vec4& backroundColor)
	{
		m_backgroundColor = backroundColor;
	}

	void SceneEnvironment::ResizeGrid(float resizeFactor)
	{
		// Implementation for resizing the grid can be added here
	}
}