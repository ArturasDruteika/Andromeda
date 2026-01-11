#include "../include/SceneComponent.hpp"
#include "Andromeda/Space/Scene/ISceneNode.hpp"


namespace Andromeda::Space
{
    SceneComponent::SceneComponent() = default;
    SceneComponent::~SceneComponent() = default;

    void SceneComponent::OnAttach(ISceneNode& node)
    {
        // Cache the transform interface pointer (safe and matches ISceneNode API).
        m_transform = node.GetTransform();
    }

    void SceneComponent::OnDetach()
    {
        m_transform = nullptr;
    }

    bool SceneComponent::IsAttached() const
    {
        return m_transform != nullptr;
    }

    ITransformable* SceneComponent::GetTransform() const
    {
        return m_transform;
    }
}
