#ifndef API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__I_SCENE_COMPONENT__HPP


#include "ISceneNode.hpp"


namespace Andromeda
{
    class ISceneComponent
    {
    public:
        virtual ~ISceneComponent() = default;

        // Called after the component is owned by a node.
        // The node reference is guaranteed valid for the duration of the attachment.
        virtual void OnAttach(ISceneNode& node) = 0;

        // Called right before the component is removed/destroyed or the node is destroyed.
        virtual void OnDetach(ISceneNode& node) = 0;
    };
}

#endif // API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
