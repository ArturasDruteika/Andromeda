#include "../include/Scene.hpp"
#include "../../../Utils/include/MathUtils.hpp"


namespace Andromeda::Rendering
{
	Scene::Scene()
		: m_sceneCenter{ glm::vec3(0.0f, 0.0f, 0.0f) }
	{
	};

	Scene::Scene(const Math::Vec3& sceneCenter)
		: m_sceneCenter{ MathUtils::ToGLM(sceneCenter) }
	{
	};

	Scene::~Scene() = default;

	Math::Vec3 Scene::GetSceneCenter() const
	{
		return MathUtils::FromGLM(m_sceneCenter);
	}
}
