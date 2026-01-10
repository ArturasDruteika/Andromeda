#ifndef API__SPACE__SCENE__SCENE_NODE__HPP
#define API__SPACE__SCENE__SCENE_NODE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneComponent.hpp"


namespace Andromeda::Space
{
    class SPACE_API SceneComponent
        : public ISceneComponent
    {
    public:
        SceneComponent();
        ~SceneComponent() override;

        void OnAttach(ISceneNode& node) override;
        void OnDetach() override;

    protected:
        bool IsAttached() const;
        ITransformable* GetTransform() const;

    private:
        ITransformable* m_transform;
    };
}

#endif // API__SPACE__SCENE__SCENE_NODE__HPP
