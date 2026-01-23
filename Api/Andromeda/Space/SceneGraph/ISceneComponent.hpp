#ifndef API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__I_SCENE_COMPONENT__HPP


namespace Andromeda
{
    class ISceneNode;

    class ISceneComponent
    {
    public:
        virtual ~ISceneComponent() = default;

        virtual void OnAttach(ISceneNode& node) = 0;
        virtual void OnDetach() = 0;
    };
}

#endif // API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
