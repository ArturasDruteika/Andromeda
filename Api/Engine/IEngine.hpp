#ifndef API__I_ENGINE__HPP
#define API__I_ENGINE__HPP


#include "GraphicsBackend.hpp"
#include "../Renderer/IRenderer.hpp"
#include "../Scene/IScene.hpp"


namespace Andromeda
{
	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual bool IsInitialized() const = 0;
		virtual GraphicsBackend GetGraphicsBackend() const = 0;
		virtual IScene& GetScene() const = 0;
		virtual IRenderer& GetRenderer() const = 0;

		virtual bool Init() = 0;
		virtual void DeInit() = 0;
	};
}


#endif // API__I_ENGINE__HPP