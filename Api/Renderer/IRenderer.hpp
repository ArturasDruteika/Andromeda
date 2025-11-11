#ifndef API__I_RENDERER__HPP
#define API__I_RENDERER__HPP


namespace Andromeda
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

		virtual bool IsInitialized() const = 0;
		virtual void Init(int width, int height, bool illuminationMode = false) = 0;
		virtual void DeInit() = 0;
		virtual void RenderFrame(IScene& scene) = 0;
	};
}


#endif // API__I_RENDERER__HPP