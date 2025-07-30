#ifndef ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP


#include "pch.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"
#include "../../../Light/include/DirectionalLight.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class SceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting();

        // Getters
        const std::unordered_map<int, IRenderableObject*>& GetLuminousObjects() const;

		// TODO: Implement the following methods once directional light is implemented
        void AddDirectionalLight(
            int id,
            const Math::Vec3& direction,
            const Math::Vec3& color = Math::Vec3(1.0f, 1.0f, 1.0f),
            float intensity = 1.0f,
            const Math::Vec3& ambient = Math::Vec3(0.1f, 0.1f, 0.1f),
            const Math::Vec3& diffuse = Math::Vec3(0.4f, 0.4f, 0.4f),
            const Math::Vec3& specular = Math::Vec3(0.4f, 0.4f, 0.4f)
        );
        void RemoveDirectionalLight(int id);

    protected:
		std::unordered_map<int, IRenderableObject*> m_luminousObjects;
        std::unordered_map<int, DirectionalLight> m_directionalLights;
    };
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP