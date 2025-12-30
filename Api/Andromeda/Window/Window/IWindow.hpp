#ifndef API__WINDOW__I_WINDOW__HPP
#define API__WINDOW__I_WINDOW__HPP


#include "../Events/IEvent.hpp"
#include <functional>
#include <string>


namespace Andromeda
{
    class IWindow
    {
    public:
        using EventCallbackFn = std::function<void(IEvent&)>;

        virtual ~IWindow() = default;

		virtual bool IsInitialized() const = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
		virtual std::string GetTitle() const = 0;
        virtual void SetTitle(const std::string& title) = 0;
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() const = 0;
        virtual void* GetNativeHandle() const = 0;  // For GL, Vulkan, DirectX
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    };
}


#endif // API_WINDOW__I_WINDOW__HPP