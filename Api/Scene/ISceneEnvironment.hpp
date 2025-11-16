#ifndef API__SCENE__I_SCENE_API__SCENE__HPP
#define API__SCENE__I_SCENE_API__SCENE__HPP


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	class ISceneEnvironment
	{
	public:
		virtual ~ISceneEnvironment() = default;

		// Getters
		virtual float GetAmbientStrength() const = 0;
		virtual const Math::Vec4& GetBackgroundColor() const = 0;
		// Setters
		virtual void SetAmbientStrength(float ambientStrength) = 0;
		virtual void SetBackgroundColor(const Math::Vec4& backroundColor) = 0;

		virtual void ResizeGrid(float resizeFactor) = 0;
	};
}


#endif // API__SCENE__I_SCENE_API__SCENE__HPP