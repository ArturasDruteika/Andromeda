#ifndef API__SPACE__SCENE__SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__SCENE_COMPONENT__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneComponent.hpp"
#include "../../Transformations/include/Transformable.hpp"


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
        ISceneNode* m_node;
    };
}

#endif // API__SPACE__SCENE__SCENE_COMPONENT__HPP
