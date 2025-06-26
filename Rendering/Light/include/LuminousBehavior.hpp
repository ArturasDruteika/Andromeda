#ifndef RENDERING__LUMINOUS_BEHAVIOR__HPP
#define RENDERING__LUMINOUS_BEHAVIOR__HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"
#include "LightProperties.hpp"
#include "LightData.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class LuminousBehavior
			: public ILightBehavior
		{
		public:
			LuminousBehavior();
			LuminousBehavior(const LightData& lightData);
			~LuminousBehavior();

			LightData GetLightData() const;

		private:
			LightData m_lightData;
		};
	}
}


#endif // RENDERING__LUMINOUS_BEHAVIOR__HPP