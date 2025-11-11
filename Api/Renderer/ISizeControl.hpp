#ifndef API__I_SIZE__HPP
#define API__I_SIZE__HPP


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


#endif // API__I_SIZE__HPP