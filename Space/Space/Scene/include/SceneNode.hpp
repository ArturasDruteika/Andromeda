// SceneNode.hpp
#ifndef API__SPACE__SCENE__SCENE_NODE__HPP
#define API__SPACE__SCENE__SCENE_NODE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneNode.hpp"
#include "pch.hpp"


namespace Andromeda::Space
{
    class SPACE_API SceneNode : public Andromeda::ISceneNode
    {
    public:
        // SceneNode owns its transform implementation.
        explicit SceneNode(std::unique_ptr<Andromeda::ITransformable> transform);

        ~SceneNode() override;

        // Transform
        Andromeda::ITransformable& GetTransform() override;
        const Andromeda::ITransformable& GetTransform() const override;

        // Hierarchy
        Andromeda::ISceneNode* GetParent() const override;

        void AttachChild(std::unique_ptr<Andromeda::ISceneNode> child) override;
        std::unique_ptr<Andromeda::ISceneNode> DetachChild(Andromeda::ISceneNode& child) override;

        void ForEachChild(const std::function<void(Andromeda::ISceneNode&)>& fn) override;
        void ForEachChild(const std::function<void(const Andromeda::ISceneNode&)>& fn) const override;

        // Components
        Andromeda::ISceneComponent& AddComponent(std::unique_ptr<Andromeda::ISceneComponent> component) override;
        bool RemoveComponent(Andromeda::ISceneComponent& component) override;

        void ForEachComponent(const std::function<void(Andromeda::ISceneComponent&)>& fn) override;
        void ForEachComponent(const std::function<void(const Andromeda::ISceneComponent&)>& fn) const override;

    private:
        // Internal helper to keep parent pointer consistent.
        // Only SceneNode modifies SceneNode parent pointers.
        void SetParentInternal(SceneNode* parent);

        // Non-owning parent pointer.
        SceneNode* m_parent = nullptr;

        // Owned transform.
        std::unique_ptr<Andromeda::ITransformable> m_transform;

        // Owned children and components.
        std::vector<std::unique_ptr<Andromeda::ISceneNode>> m_children;
        std::vector<std::unique_ptr<Andromeda::ISceneComponent>> m_components;
    };
}

#endif // API__SPACE__SCENE__SCENE_NODE__HPP
