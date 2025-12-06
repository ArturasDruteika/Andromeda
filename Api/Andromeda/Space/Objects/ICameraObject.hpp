#ifndef API__OBJECTS__I_CAMERA_OBJECT__HPP
#define API__OBJECTS__I_CAMERA_OBJECT__HPP


#include "IObject.hpp"
#include "ITransformable.hpp"


namespace Andromeda
{
	class ICameraObject
		: public IObject
		, public ITransformable
	{
	public:
		virtual ~ICameraObject() = default;
	};
}


#endif // API__OBJECTS__I_CAMERA_OBJECT__HPP