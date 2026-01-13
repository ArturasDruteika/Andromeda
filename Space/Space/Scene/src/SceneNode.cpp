// SceneNode.cpp
#include "../include/SceneNode.hpp"
#include "Andromeda/Space/Scene/ISceneComponent.hpp"

#include "spdlog/spdlog.h"


namespace Andromeda::Space
{
    SceneNode::SceneNode(std::unique_ptr<ITransformable> transform)
        : m_transform(std::move(transform))
    {
        if (m_transform == nullptr)
        {
            spdlog::error("SceneNode requires a non-null transform.");
        }
    }

    SceneNode::~SceneNode()
    {
        // Detach components first (they may rely on child hierarchy still existing).
        for (auto& component : m_components)
        {
            if (component != nullptr)
            {
                component->OnDetach();
            }
        }
        m_components.clear();

        // Ensure children no longer reference this as a parent before they are destroyed.
        for (auto& child : m_children)
        {
            SceneNode* childNode = dynamic_cast<SceneNode*>(child.get());
            if (childNode != nullptr)
            {
                childNode->SetParentInternal(nullptr);
            }
        }
        m_children.clear();

        m_parent = nullptr;
        m_transform.reset();
    }

    ITransformable& SceneNode::GetTransform()
    {
        return *m_transform;
    }

    const ITransformable& SceneNode::GetTransform() const
    {
        return *m_transform;
    }

    ISceneNode* SceneNode::GetParent() const
    {
        return m_parent;
    }

    void SceneNode::AttachChild(std::unique_ptr<ISceneNode> child)
    {
        if (child == nullptr)
        {
            return;
        }

        if (child.get() == this)
        {
            spdlog::error("Cannot attach node to itself.");
        }

        // Best-effort support for "removing from old parent" while still taking unique_ptr:
        // If the child reports a parent, attempt to detach it from that parent and use the returned ownership.
        // IMPORTANT: This only works safely if the caller is not still double-owning the same node elsewhere.
        ISceneNode* oldParent = child->GetParent();
        if (oldParent != nullptr)
        {
            std::unique_ptr<ISceneNode> transferred = oldParent->DetachChild(*child);
            if (transferred != nullptr)
            {
                // Avoid double delete: release the passed-in unique_ptr and use the transferred ownership.
                child.release();
                child = std::move(transferred);
            }
            else
            {
                // Could not detach; refuse to attach to keep invariants safe.
                throw std::runtime_error("AttachChild failed: could not detach child from its old parent.");
            }
        }

        SceneNode* childNode = dynamic_cast<SceneNode*>(child.get());
        if (childNode == nullptr)
        {
            spdlog::error("AttachChild requires child to be a SceneNode instance.");
        }

        childNode->SetParentInternal(this);
        m_children.push_back(std::move(child));
    }

    std::unique_ptr<ISceneNode> SceneNode::DetachChild(ISceneNode& child)
    {
        for (size_t i = 0; i < m_children.size(); ++i)
        {
            if (m_children[i].get() == &child)
            {
                SceneNode* childNode = dynamic_cast<SceneNode*>(m_children[i].get());
                if (childNode != nullptr)
                {
                    childNode->SetParentInternal(nullptr);
                }

                std::unique_ptr<ISceneNode> out = std::move(m_children[i]);
                m_children.erase(m_children.begin() + static_cast<long>(i));
                return out;
            }
        }

        return nullptr;
    }

    void SceneNode::ForEachChild(const std::function<void(ISceneNode&)>& fn)
    {
        for (auto& child : m_children)
        {
            fn(*child);
        }
    }

    void SceneNode::ForEachChild(const std::function<void(const ISceneNode&)>& fn) const
    {
        for (const auto& child : m_children)
        {
            fn(*child);
        }
    }

    ISceneComponent& SceneNode::AddComponent(std::unique_ptr<ISceneComponent> component)
    {
        if (component == nullptr)
        {
            spdlog::error("AddComponent requires a non-null component.");
        }

        component->OnAttach(*this);
        m_components.push_back(std::move(component));
        return *m_components.back();
    }

    bool SceneNode::RemoveComponent(ISceneComponent& component)
    {
        for (size_t i = 0; i < m_components.size(); ++i)
        {
            if (m_components[i].get() == &component)
            {
                m_components[i]->OnDetach();
                m_components.erase(m_components.begin() + static_cast<long>(i));
                return true;
            }
        }

        return false;
    }

    void SceneNode::ForEachComponent(const std::function<void(ISceneComponent&)>& fn)
    {
        for (auto& component : m_components)
        {
            fn(*component);
        }
    }

    void SceneNode::ForEachComponent(const std::function<void(const ISceneComponent&)>& fn) const
    {
        for (const auto& component : m_components)
        {
            fn(*component);
        }
    }

    void SceneNode::SetParentInternal(SceneNode* parent)
    {
        m_parent = parent;
    }
}
