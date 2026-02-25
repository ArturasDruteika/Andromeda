#ifndef SPACE__SCENE__SCENE_NODE_MANAGER__HPP
#define SPACE__SCENE__SCENE_NODE_MANAGER__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "../../SceneGraph/include/SceneNode.hpp"
#include "SceneLighting.hpp"
#include "SceneObjects.hpp"
#include "Andromeda/Space/Scene/ISceneNodeManager.hpp"
#include "pch.hpp"

#include <memory>


namespace Andromeda::Space
{
	class SPACE_API SceneNodeManager
		: public virtual ISceneNodeManager
		, public SceneObjects
		, public SceneLighting
	{
	public:
		SceneNodeManager();
		~SceneNodeManager() override;

		void AttachNode(std::unique_ptr<ISceneNode> node) override;

		// Convenience overload for concrete nodes.
		void AttachNode(std::unique_ptr<SceneNode> node);

		void AddObject(int id, IGeometricObject* object) override;
		void RemoveObject(int id) override;

	protected:
		void RegisterNode(SceneNode& node);
		void RegisterNodeRecursive(SceneNode& node);

	private:
		std::unique_ptr<SceneNode> m_rootNode;
	};
}


#endif // SPACE__SCENE__SCENE_NODE_MANAGER__HPP