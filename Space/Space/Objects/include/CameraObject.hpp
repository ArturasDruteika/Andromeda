#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "Object.hpp"
#include "Transformable.hpp"
#include "Andromeda/Space/Objects/ICameraObject.hpp"


namespace Andromeda::Space
{
	class CameraObject
		: public virtual ICameraObject
		, public Object
		, public Transformable
	{
	public:
		CameraObject(const Math::Vec3& centerPosition);
		~CameraObject() override;
	};
}


#endif // SPACE__OBJECTS__CAMERA_OBJECT__HPP