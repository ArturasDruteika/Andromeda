#ifndef ENVIRONMENT__ABSTRACTS_SCENE__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE__HPP


#include "pch.hpp"
#include "SceneObjects.hpp"
#include "SceneEnvironment.hpp"
#include "SceneState.hpp"


namespace Andromeda::Rendering
{
    class Scene :
        public SceneObjects,
        public SceneEnvironment,
        public SceneState
    {
    public:
        Scene();
        ~Scene();
    };
}


#endif // ENVIRONMENT__ENVIRONMENT__HPP