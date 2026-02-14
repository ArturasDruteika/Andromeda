#ifndef SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP
#define SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP


#include "SceneComponent.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"


namespace Andromeda::Space
{
    class SPACE_API LightComponent
        : public SceneComponent
    {
    public:
        LightComponent(int id, const ILightObject* lightObject);
        ~LightComponent() override;

        int GetId() const;
        const ILightObject* GetLightObject() const;

    private:
        int m_id;
        const ILightObject* m_lightObject;
    };
}


#endif // SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP