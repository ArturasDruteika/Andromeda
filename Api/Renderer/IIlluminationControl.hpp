#ifndef API__RENDERER__I_ILLUMINATION_CONTROL__HPP
#define API__RENDERER__I_ILLUMINATION_CONTROL__HPP


namespace Andromeda
{
	class IIlluminationControl
	{
	public:
		virtual ~IIlluminationControl();

		// Getters
		virtual bool IsIlluminationMode() const = 0;
		// Setters
		virtual void SetIlluminationMode(bool mode) = 0;
	};
}


#endif // API__RENDERER__I_ILLUMINATION_CONTROL__HPP