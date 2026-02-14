#ifndef SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP
#define SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP


#include "SceneComponent.hpp"
#include "Andromeda/Space/Objects/IGeometricObject.hpp"


namespace Andromeda::Space
{
    class SPACE_API ObjectComponent
        : public SceneComponent
    {
    public:
        ObjectComponent(int id, IGeometricObject* object);
        ~ObjectComponent() override;

        int GetId() const;
        IGeometricObject* GetObject() const;

    private:
        int m_id;
        IGeometricObject* m_object;
    };
}


#endif // SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP