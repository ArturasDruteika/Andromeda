#ifndef RENDERER__SIZE__HPP
#define RENDERER__SIZE__HPP


namespace Andromeda::Rendering
{
	class SizeControl
	{
	public:
		SizeControl(int width = 800, int height = 600);
		~SizeControl();

		// Getters
		int GetWidth() const;
		int GetHeight() const;

		void Resize(int width, int height);

	protected:
		int m_width;
		int m_height;
	};
}


#endif // RENDERER__SIZE__HPP