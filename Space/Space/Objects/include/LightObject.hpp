#ifndef ANDROMEDA__SPACE__LIGHT_OBJECT__HPP
#define ANDROMEDA__SPACE__LIGHT_OBJECT__HPP


#include "Object.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Light/LightTypes.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"


namespace Andromeda::Space
{
	class SPACE_API LightObject
		: public virtual ILightObject
		, public Object
	{
	public:
		LightObject(const LightType& lightType);
		~LightObject() override;

		// Getters
		const LightType& GetLightType() const override;

	protected:
		LightType m_lightType;
	};
}


#endif // ANDROMEDA__SPACE__LIGHT_OBJECT__HPP