#ifndef SPACE__SCENE__SCENE_LIGHTING__HPP
#define SPACE__SCENE__SCENE_LIGHTING__HPP


#include "../../Light/include/DirectionalLight.hpp"
#include "../../Light/include/PointLight.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneLighting.hpp"


namespace Andromeda::Space
{
    class SPACE_API SceneLighting
		: public virtual ISceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting() override;

        // Getters
        const std::unordered_map<int, const IDirectionalLight*>& GetDirectionalLights() const override;
        const std::unordered_map<int, const IPointLight*>& GetPointLights() const override;
        const std::unordered_map<int, const ILightObject*>& GetLightObjects() const override;

        void AddLightObject(int id, const ILightObject* pLightObject);
		void RemoveLightObject(int id);

    protected:
        std::unordered_map<int, const IDirectionalLight*> m_directionalLights;
        std::unordered_map<int, const IPointLight*> m_pointLights;
		std::unordered_map<int, const ILightObject*> m_lightObjects;
    };
}


#endif // SPACE__SCENE__SCENE_LIGHTING__HPP