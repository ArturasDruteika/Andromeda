#ifndef API__RENDERER__I_RENDERER__HPP
#define API__RENDERER__I_RENDERER__HPP


#include "ICameraControl.hpp"
#include "IGridControl.hpp"
#include "IIlluminationControl.hpp"
#include "ISizeControl.hpp"


namespace Andromeda
{
	class IRenderer 
		: public ICameraControl
		, public IGridControl
		, public IIlluminationControl
		, public ISizeControl
	{
	public:
		virtual ~IRenderer() = default;

		virtual bool IsInitialized() const = 0;
		virtual void Init(int width, int height, bool illuminationMode = false) = 0;
		virtual void DeInit() = 0;
		virtual void RenderFrame(IScene& scene) = 0;
	};
}


#endif // API__RENDERER__I_RENDERER__HPP