#ifndef SPACE__LUMINOUS_BEHAVIOR__HPP
#define SPACE__LUMINOUS_BEHAVIOR__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Light/ILuminousBehavior.hpp"
#include "Andromeda/Light/LightTypes.hpp"
#include "Light.hpp"


namespace Andromeda::Space
{
	class SPACE_API LuminousBehavior
		: public virtual ILuminousBehavior
	{
	public:
		LuminousBehavior(Light light, const LightType& type);
		~LuminousBehavior() override;

		LightType GetType() const override;
		const Light& GetLight() const override;

	private:
		LightType m_type;
		Light m_light;
	};
}


#endif // SPACE__LUMINOUS_BEHAVIOR__HPP