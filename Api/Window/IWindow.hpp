#ifndef API__WINDOW__I_WINDOW__HPP
#define API__WINDOW__I_WINDOW__HPP


#include <string>


class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual void SetTitle(const std::string& title) = 0;

    virtual void* GetNativeHandle() const = 0;  // For GL, Vulkan, DirectX
};


#endif // API_WINDOW__I_WINDOW__HPP