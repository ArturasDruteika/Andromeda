#ifndef API_RENDERER__I_SIZE__HPP
#define API_RENDERER__I_SIZE__HPP


namespace Andromeda
{
	class ISizeControl
	{
	public:
		virtual ~ISizeControl();

		// Getters
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Resize(int width, int height) = 0;
	};
}


#endif // API_RENDERER__I_SIZE__HPP