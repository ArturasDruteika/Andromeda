#ifndef ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP


#include "pch.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"
#include "../../../Light/LightTypes/include/DirectionalLight.hpp"
#include "../../../Light/LightTypes/include/PointLight.hpp"
#include "../../../Light/Support/include/LightTypes.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class SceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting();

        // Getters
        const std::unordered_map<int, const DirectionalLight*> GetDirectionalLights() const;
        const std::unordered_map<int, const PointLight*> GetPointLights() const;
        const std::unordered_map<int, IRenderableObject*>& GetLuminousObjects() const;

    protected:
        std::unordered_map<int, IRenderableObject*> m_luminousObjects;

    private:
        // Fixed: return map of pointers, not objects
        template <typename TLight>
        std::unordered_map<int, const TLight*> ExtractLightsOfType(LightType type) const;
    };
}

#endif // ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
