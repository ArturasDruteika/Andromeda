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

	void SceneLighting::AddLightObject(int id, const ILightObject* pLightObject)
	{
		m_lightObjects[id] = pLightObject;
		if (pLightObject->GetLightType() == LightType::Directional)
		{
			const IDirectionalLight* directionalLight = dynamic_cast<const IDirectionalLight*>(pLightObject);
			if (directionalLight)
			{
				m_directionalLights[id] = directionalLight;
			}
		}
		else if (pLightObject->GetLightType() == LightType::Point)
		{
			const IPointLight* pointLight = dynamic_cast<const IPointLight*>(pLightObject);
			if (pointLight)
			{
				m_pointLights[id] = pointLight;
			}
		}
	}

	void SceneLighting::RemoveLightObject(int id)
	{
		auto lightObjectIt = m_lightObjects.find(id);
		if (lightObjectIt != m_lightObjects.end())
		{
			const ILightObject* lightObject = lightObjectIt->second;
			if (lightObject->GetLightType() == LightType::Directional)
			{
				auto directionalLightIt = m_directionalLights.find(id);
				if (directionalLightIt != m_directionalLights.end())
				{
					delete directionalLightIt->second;
					m_directionalLights.erase(directionalLightIt);
				}
			}
			else if (lightObject->GetLightType() == LightType::Point)
			{
				auto pointLightIt = m_pointLights.find(id);
				if (pointLightIt != m_pointLights.end())
				{
					delete pointLightIt->second;
					m_pointLights.erase(pointLightIt);
				}
			}
			delete lightObject;
			m_lightObjects.erase(lightObjectIt);
		}
	}
}