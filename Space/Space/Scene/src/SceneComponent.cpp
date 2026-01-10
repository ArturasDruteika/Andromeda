#include "../include/SceneComponent.hpp"


namespace Andromeda::Space
{
    SceneComponent::SceneComponent() = default;

    SceneComponent::~SceneComponent() = default;

    void SceneComponent::OnAttach(ISceneNode& node)
    {
        // Cache the transform so derived components can access it cheaply.
        m_transform = &node.GetTransform();
    }

    void SceneComponent::OnDetach()
    {
        m_transform = nullptr;
    }

    bool SceneComponent::IsAttached() const
    {
        return m_transform != nullptr;
    }

    Andromeda::ITransformable* SceneComponent::GetTransform() const
    {
        return m_transform;
    }
}