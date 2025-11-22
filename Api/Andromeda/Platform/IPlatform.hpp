#ifndef API__PLATFORM__I_PLATFORM__HPP
#define API__PLATFORM__I_PLATFORM__HPP


#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"
#include "../GraphicsContext/IGraphicsContext.hpp"
#include "../Window/IWindow.hpp"
#include <memory>
#include <string>


namespace Andromeda
{
	class IPlatform
	{
	public:
		virtual ~IPlatform() = default;

		virtual bool IsInitialized() const = 0;
		virtual GraphicsBackend GetGraphicsBackend() const = 0;
		virtual bool Init(int width, int height, const std::string& title) = 0;
        virtual void Shutdown() = 0;
        virtual IGraphicsContext* GetGraphicsContext() const = 0;
        virtual IWindow* GetWindow() const = 0;
	};

	ANDROMEDA_API std::unique_ptr<IPlatform> CreatePlatform(const GraphicsBackend& graphicsBackend);
}


#endif // API__PLATFORM__I_PLATFORM__HPP