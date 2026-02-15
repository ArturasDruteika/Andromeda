#ifndef API__RENDERER__I_RENDERER__HPP
#define API__RENDERER__I_RENDERER__HPP


#include "IGridControl.hpp"
#include "IIlluminationControl.hpp"
#include "ISizeControl.hpp"
#include "../Space/Scene/IScene.hpp"
#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"


namespace Andromeda
{
	class IRenderer 
		: public IGridControl
		, public IIlluminationControl
		, public ISizeControl
	{
	public:
		virtual ~IRenderer() = default;

		// Getters
		virtual bool IsInitialized() const = 0;
		virtual void* GetFrameTextureHandle() const = 0;

		virtual void Init(int width, int height, bool illuminationMode = false) = 0;
		virtual void DeInit() = 0;
		virtual void RenderFrame(IScene& scene) = 0;
	};

	ANDROMEDA_API std::unique_ptr<IRenderer> CreateRenderer(const GraphicsBackend& graphicsBackend);
}


#endif // API__RENDERER__I_RENDERER__HPP