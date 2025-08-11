#ifndef RENDERER__I_RENDERER__HPP
#define RENDERER__I_RENDERER__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../include/ICameraControl.hpp"
#include "../include/IGridControl.hpp"
#include "../include/IIlluminationControl.hpp"
#include "../include/ISizeControl.hpp"
#include "../../../Scene/Interfaces/include/IScene.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IRenderer
		: public ICameraControl
		, public IGridControl
		, public IIlluminationControl
		, public ISizeControl
	{
	public:
		virtual ~IRenderer();

		// Getters
		virtual bool IsInitialized() const = 0;

		virtual void Init(int width, int height, bool illuminationMode = false) = 0;
		virtual void DeInit() = 0;
		virtual void RenderFrame(IScene& scene) = 0;
	};
}


#endif // RENDERER__I_RENDERER__HPP