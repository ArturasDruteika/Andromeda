#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "Object.hpp"
#include "../../Transformations/include/Rotatable.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Objects/ICameraObject.hpp"


namespace Andromeda::Space
{
	class SPACE_API CameraObject
		: public virtual ICameraObject
		, public Object
	{
	public:
		CameraObject();
		CameraObject(const Math::Vec3& centerPosition);
		~CameraObject() override;
	};
}


#endif // SPACE__OBJECTS__CAMERA_OBJECT__HPP