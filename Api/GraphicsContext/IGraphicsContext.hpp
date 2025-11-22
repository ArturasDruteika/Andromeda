#ifndef API__GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP
#define API__GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP


#include "../Window/IWindow.hpp"


namespace Andromeda
{
    class IGraphicsContext
    {
    public:
        virtual ~IGraphicsContext() = default;

        virtual bool IsInitialized() const = 0;
        virtual bool Init(IWindow &window) = 0;
        virtual void MakeCurrent() = 0;
        virtual void Present() = 0;
    };
}


#endif // API_GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP