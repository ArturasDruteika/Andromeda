#ifndef API__SCENE__I_SCENE_UPDATE_HOOKS__HPP
#define API__SCENE__I_SCENE_UPDATE_HOOKS__HPP


#include <cstdint>
#include <functional>


namespace Andromeda
{
	class ISceneUpdateHooks
	{
	public:
		using Callback = std::function<void(float)>;

		struct Handle
		{
			std::uint64_t id = 0;
		};

	public:
		virtual ~ISceneUpdateHooks() = default;

		virtual Handle Add(Callback callback) = 0;
		virtual void Remove(Handle handle) = 0;
		virtual void Clear() = 0;
		virtual void Run(float deltaTime) = 0;
	};
}


#endif // API__SCENE__I_SCENE_UPDATE_HOOKS__HPP

