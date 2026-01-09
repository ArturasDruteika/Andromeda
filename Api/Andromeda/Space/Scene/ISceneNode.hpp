#ifndef API__SPACE__SCENE__I_SCENE_NODE__HPP
#define API__SPACE__SCENE__I_SCENE_NODE__HPP


#include "ISceneComponent.hpp"
#include "../Transformations/ITransformable.hpp"

#include <functional>
#include <memory>


namespace Andromeda
{
    class ISceneNode
    {
    public:
        virtual ~ISceneNode() = default;

        // Transform
        virtual ITransformable& GetTransform() = 0;
        virtual const ITransformable& GetTransform() const = 0;

        // Hierarchy
        virtual ISceneNode* GetParent() const = 0;

        // Parent takes ownership of the child node.
        // Implementation must keep invariants consistent (child parent pointer, removing from old parent, etc.).
        virtual void AttachChild(std::unique_ptr<ISceneNode> child) = 0;

        // Detach a child and return ownership to the caller (nullptr if not found).
        virtual std::unique_ptr<ISceneNode> DetachChild(ISceneNode& child) = 0;

        // Non-owning traversal (keeps storage private).
        virtual void ForEachChild(const std::function<void(ISceneNode&)>& fn) = 0;
        virtual void ForEachChild(const std::function<void(const ISceneNode&)>& fn) const = 0;

        // Components
        virtual ISceneComponent& AddComponent(std::unique_ptr<ISceneComponent> component) = 0;
        virtual bool RemoveComponent(ISceneComponent& component) = 0;

        virtual void ForEachComponent(const std::function<void(ISceneComponent&)>& fn) = 0;
        virtual void ForEachComponent(const std::function<void(const ISceneComponent&)>& fn) const = 0;
    };
}

#endif // API__SPACE__SCENE__I_SCENE_NODE__HPP
