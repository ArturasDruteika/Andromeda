#ifndef API__SPACE__SCENE__SCENE_NODE__HPP
#define API__SPACE__SCENE__SCENE_NODE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/SceneGraph/ISceneNode.hpp"
#include "pch.hpp"


namespace Andromeda::Space
{
    class SPACE_API SceneNode
        : public ISceneNode
    {
    public:
        // SceneNode owns its transform implementation.
        explicit SceneNode(std::unique_ptr<ITransformable> transform);

        ~SceneNode() override;

        // Transform
        ITransformable& GetTransform() override;
        const ITransformable& GetTransform() const override;

        // Hierarchy
        ISceneNode* GetParent() const override;

        void AttachChild(std::unique_ptr<ISceneNode> child) override;
        std::unique_ptr<ISceneNode> DetachChild(ISceneNode& child) override;

        void ForEachChild(const std::function<void(ISceneNode&)>& fn) override;
        void ForEachChild(const std::function<void(const ISceneNode&)>& fn) const override;

        // Components
        ISceneComponent& AddComponent(std::unique_ptr<ISceneComponent> component) override;
        bool RemoveComponent(ISceneComponent& component) override;

        void ForEachComponent(const std::function<void(ISceneComponent&)>& fn) override;
        void ForEachComponent(const std::function<void(const ISceneComponent&)>& fn) const override;

    private:
        // Internal helper to keep parent pointer consistent.
        // Only SceneNode modifies SceneNode parent pointers.
        void SetParentInternal(SceneNode* parent);

    private:
        // Non-owning parent pointer.
        SceneNode* m_parent = nullptr;

        // Owned transform.
        std::unique_ptr<ITransformable> m_transform;

        // Owned children and components.
        std::vector<std::unique_ptr<ISceneNode>> m_children;
        std::vector<std::unique_ptr<ISceneComponent>> m_components;
    };
}

#endif // API__SPACE__SCENE__SCENE_NODE__HPP
