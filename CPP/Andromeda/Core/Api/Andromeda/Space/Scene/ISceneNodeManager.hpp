#ifndef API__SCENE__I_SCENE_NODE_MANAGER__HPP
#define API__SCENE__I_SCENE_NODE_MANAGER__HPP


#include "Andromeda/Space/SceneGraph/ISceneNode.hpp"

#include <memory>


namespace Andromeda
{
	class ISceneNodeManager
	{
	public:
		virtual ~ISceneNodeManager() = default;

		virtual void AttachNode(std::unique_ptr<ISceneNode> node) = 0;
	};
}


#endif // API__SCENE__I_SCENE_NODE_MANAGER__HPP