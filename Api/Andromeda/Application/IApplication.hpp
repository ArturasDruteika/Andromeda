#ifndef API__APPLICATION__I_APPLICATION__HPP
#define API__APPLICATION__I_APPLICATION__HPP


#include "../Components/GraphicsBackend.hpp"
#include "../MacroExports/MacroExports.hpp"
#include "../Space/Scene/IScene.hpp"

#include <memory>


namespace Andromeda
{
    class IApplication
    {
    public:
        virtual ~IApplication() = default;

        virtual bool Init(unsigned int width, unsigned int height, const std::string& title) = 0;
        virtual void DeInit() = 0;

        virtual void SetScene(IScene* pScene) = 0;
        virtual int Run() = 0;
    };

    ANDROMEDA_API std::unique_ptr<IApplication> CreateApp(const GraphicsBackend& graphicsBackend);
}

#endif // API__APPLICATION__I_APPLICATION__HPP
