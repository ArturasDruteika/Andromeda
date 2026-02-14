#ifndef API__ENGINE__GRAPHICS_BACKEND__HPP
#define API__ENGINE__GRAPHICS_BACKEND__HPP


#include <string_view>


namespace Andromeda
{
	enum class GraphicsBackend : int
	{
		None = 0,
		OpenGL = 1,
		Vulkan = 2
	};

    constexpr std::string_view GraphicsBackendString(const GraphicsBackend& backend) noexcept
    {
        switch (backend)
        {
            case GraphicsBackend::None:   return "None";
            case GraphicsBackend::OpenGL: return "OpenGL";
            case GraphicsBackend::Vulkan: return "Vulkan";
            default:                      return "Unknown";
        }
    }
}


#endif // API__ENGINE__GRAPHICS_BACKEND__HPP