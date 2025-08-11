#ifndef ENVIRONMENT__I_SCENE__HPP
#define ENVIRONMENT__I_SCENE__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "ISceneObjects.hpp"
#include "ISceneLighting.hpp"
#include "ISceneEnvironment.hpp"
#include "ISceneState.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API IScene :
        public ISceneObjects,
        public ISceneLighting,
        public ISceneEnvironment,
        public ISceneState
    {
    public:
        virtual ~IScene();

		// Getters
        virtual glm::vec3 GetSceneCenter() const = 0;
    };
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP