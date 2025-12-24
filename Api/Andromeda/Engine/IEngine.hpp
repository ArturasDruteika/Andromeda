#ifndef API__ENGINE__I_ENGINE__HPP
#define API__ENGINE__I_ENGINE__HPP


#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"
#include "../Renderer/IRenderer.hpp"
#include "../Space/Scene/IScene.hpp"
#include "../Window/IEvent.hpp"
#include <memory>


namespace Andromeda
{
	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual bool IsInitialized() const = 0;
		virtual GraphicsBackend GetGraphicsBackend() const = 0;
		virtual IRenderer* GetRenderer() const = 0;

		virtual bool Init() = 0;
		virtual void DeInit() = 0;

		virtual void OnEvent(IEvent& event) = 0;
	};

	ANDROMEDA_API std::unique_ptr<IEngine> CreateEngine(const GraphicsBackend& graphicsBackend);
}


#endif // API__ENGINE__I_ENGINE__HPP