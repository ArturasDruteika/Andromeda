#ifndef API_RENDERER__I_ILLUMINATION_CONTROL__HPP
#define API_RENDERER__I_ILLUMINATION_CONTROL__HPP


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


#endif // API_RENDERER__I_ILLUMINATION_CONTROL__HPP