#include "../include/CameraObject.hpp"


namespace Andromeda::Space
{
	CameraObject::CameraObject() = default;

	CameraObject::CameraObject(const Math::Vec3& centerPosition)
		: Translatable{ centerPosition }
	{
	}

	CameraObject::~CameraObject() = default;
}
