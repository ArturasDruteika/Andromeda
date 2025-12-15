#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "Object.hpp"
#include "../../Transformations/include/Rotatable.hpp"
#include "../../Transformations/include/Translatable.hpp"
#include "Andromeda/Space/Objects/ICameraObject.hpp"


namespace Andromeda::Space
{
	class CameraObject
		: public virtual ICameraObject
		, public Object
		, public Rotatable
		, public Translatable
	{
	public:
		CameraObject();
		CameraObject(const Math::Vec3& centerPosition);
		~CameraObject() override;
	};
}


#endif // SPACE__OBJECTS__CAMERA_OBJECT__HPP