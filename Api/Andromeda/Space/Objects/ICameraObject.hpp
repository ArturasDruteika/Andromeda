#ifndef API__OBJECTS__I_CAMERA_OBJECT__HPP
#define API__OBJECTS__I_CAMERA_OBJECT__HPP


#include "IObject.hpp"
#include "../Transformations/IRotatable.hpp"
#include "../Transformations/ITranslatable.hpp"


namespace Andromeda
{
	class ICameraObject
		: public virtual IObject
		, public virtual IRotatable
		, public virtual ITranslatable
	{
	public:
		virtual ~ICameraObject() = default;
	};
}


#endif // API__OBJECTS__I_CAMERA_OBJECT__HPP