#ifndef SPACE__LUMINOUS_BEHAVIOR__HPP
#define SPACE__LUMINOUS_BEHAVIOR__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../Interfaces/include/ILightBehavior.hpp"
#include "../../Support/include/LightTypes.hpp"
#include "Light.hpp"


namespace Andromeda::Space
{
	class SPACE_API LuminousBehavior
		: public ILightBehavior
	{
	public:
		LuminousBehavior(Light light, const LightType& type);
		~LuminousBehavior();

		LightType GetType() const;
		const Light& GetLight() const;

	private:
		LightType m_type;
		Light m_light;
	};
}


#endif // SPACE__LUMINOUS_BEHAVIOR__HPP