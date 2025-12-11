#include "../include/CameraObject.hpp"


namespace Andromeda::Space
{
	CameraObject::CameraObject(const Math::Vec3& centerPosition)
		: Transformable(centerPosition)
	{
	}

	CameraObject::~CameraObject() = default;
}
