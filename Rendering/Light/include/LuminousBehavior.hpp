#ifndef RENDERING__LUMINOUS_BEHAVIOR__HPP
#define RENDERING__LUMINOUS_BEHAVIOR__HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class LuminousBehavior
			: ILightBehavior
		{
		public:
			virtual ~LuminousBehavior();
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP