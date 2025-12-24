#include "../include/SceneLighting.hpp"


namespace Andromeda::Space
{
	SceneLighting::SceneLighting()
		: m_directionalLights{}
		, m_pointLights{}
		, m_lightObjects{}
	{
	}

	SceneLighting::~SceneLighting()
	{
		for (const auto& [id, light] : m_directionalLights)
		{
			delete light;
		}
		for (const auto& [id, light] : m_pointLights)
		{
			delete light;
		}
		for (const auto& [id, lightObject] : m_lightObjects)
		{
			delete lightObject;
		}
	}

	const std::unordered_map<int, const IDirectionalLight*>& SceneLighting::GetDirectionalLights() const
	{
		return m_directionalLights;
	}

	const std::unordered_map<int, const IPointLight*>& SceneLighting::GetPointLights() const
	{
		return m_pointLights;
	}

	const std::unordered_map<int, const ILightObject*>& SceneLighting::GetLightObjects() const
	{
		return m_lightObjects;
	}
}