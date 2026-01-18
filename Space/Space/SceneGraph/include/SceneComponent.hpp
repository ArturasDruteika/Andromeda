#ifndef API__SPACE__SCENE__SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__SCENE_COMPONENT__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/SceneGraph/ISceneComponent.hpp"


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

    private:
        ISceneNode* m_node;
    };
}

#endif // API__SPACE__SCENE__SCENE_COMPONENT__HPP
