#ifndef API__SPACE__SCENE__SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__SCENE_COMPONENT__HPP

#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneComponent.hpp"
#include "../../Transformations/include/Transformable.hpp" // optional; see note below

namespace Andromeda::Space
{
    class SPACE_API SceneComponent : public Andromeda::ISceneComponent
    {
    public:
        SceneComponent();
        ~SceneComponent() override;

        void OnAttach(Andromeda::ISceneNode& node) override;
        void OnDetach() override;

    protected:
        bool IsAttached() const;
        Andromeda::ITransformable* GetTransform() const;

    private:
        Andromeda::ITransformable* m_transform = nullptr;
    };
}

#endif // API__SPACE__SCENE__SCENE_COMPONENT__HPP
