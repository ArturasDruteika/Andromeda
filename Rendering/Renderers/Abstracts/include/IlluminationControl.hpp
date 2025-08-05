#ifndef RENDERER__ILLUMINATION_CONTROL__HPP
#define RENDERER__ILLUMINATION_CONTROL__HPP


namespace Andromeda::Rendering
{
	class IlluminationControl
	{
	public:
		IlluminationControl();
		~IlluminationControl();

		// Getters
		bool IsIlluminationMode() const;
		// Setters
		void SetIlluminationMode(bool mode);

	protected:
		bool m_isIlluminationMode;
	};
}


#endif // RENDERER__ILLUMINATION_CONTROL__HPP