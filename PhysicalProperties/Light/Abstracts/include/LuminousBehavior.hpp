#ifndef PHYSICAL_PROPERTIES__LUMINOUS_BEHAVIOR__HPP
#define PHYSICAL_PROPERTIES__LUMINOUS_BEHAVIOR__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../Interfaces/include/ILightBehavior.hpp"
#include "../../Support/include/LightTypes.hpp"
#include "Light.hpp"


namespace Andromeda::PhysicalProperties
{
	class PHYSICAL_PROPERTIES_API LuminousBehavior
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


#endif // PHYSICAL_PROPERTIES__LUMINOUS_BEHAVIOR__HPP