#include "../include/SceneLighting.hpp"
#include "../../../Utils/include/MathUtils.hpp"


namespace Andromeda::Rendering
{
	SceneLighting::SceneLighting() = default;

	SceneLighting::~SceneLighting() = default;

	void SceneLighting::AddDirectionalLight(
		int id, 
		const Math::Vec3& direction, 
		const Math::Vec3& color, 
		float intensity, 
		const Math::Vec3& ambient, 
		const Math::Vec3& diffuse, 
		const Math::Vec3& specular
	)
	{
		m_directionalLights.emplace(
			id, 
			DirectionalLight(
				MathUtils::ToGLM(direction),
				MathUtils::ToGLM(color),
				intensity,
				MathUtils::ToGLM(ambient),
				MathUtils::ToGLM(diffuse),
				MathUtils::ToGLM(specular)
			)
		);
	}

	void SceneLighting::RemoveDirectionalLight(int id)
	{
		auto it = m_directionalLights.find(id);
		if (it != m_directionalLights.end())
		{
			m_directionalLights.erase(it);
		}
	}
}
