#include "../include/SceneComponent.hpp"
#include "Andromeda/Space/SceneGraph/ISceneNode.hpp"


namespace Andromeda::Space
{
    SceneComponent::SceneComponent()
        : m_node{ nullptr }
    {
	}

    SceneComponent::~SceneComponent() = default;

    void SceneComponent::OnAttach(ISceneNode& node)
    {
        m_node = &node;
    }

    void SceneComponent::OnDetach()
    {
        m_node = nullptr;
    }
}
