#ifndef API__OBJECTS__I_CAMERA_OBJECT__HPP
#define API__OBJECTS__I_CAMERA_OBJECT__HPP


#include "IObject.hpp"


namespace Andromeda
{
	class ICameraObject
		: public virtual IObject
	{
	public:
		virtual ~ICameraObject() = default;
	};
}


#endif // API__OBJECTS__I_CAMERA_OBJECT__HPP