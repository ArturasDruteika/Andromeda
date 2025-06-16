#ifndef RENDERING__NON_LUMINOUS_BEHAVIOR_HPP
#define RENDERING__NON_LUMINOUS_BEHAVIOR_HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"

namespace Andromeda
{
	namespace Rendering
	{
		class NonLuminousBehavior
			: public ILightBehavior
		{
			~NonLuminousBehavior();
		};
	}
}


#endif // RENDERING__NON_LUMINOUS_BEHAVIOR_HPP