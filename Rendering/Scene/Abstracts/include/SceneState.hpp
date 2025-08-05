#ifndef ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP


#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
	class SceneState
	{
	public:
		SceneState();
		~SceneState();

		bool StateChanged(const std::unordered_map<int, IRenderableObject*>& objects) const;
	};
}


#endif // ENVIRONMENT__ABSTRACTS_SCENE_STATE__HPP