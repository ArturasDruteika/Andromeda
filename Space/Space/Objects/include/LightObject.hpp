#ifndef ANDROMEDA__SPACE__LIGHT_OBJECT__HPP
#define ANDROMEDA__SPACE__LIGHT_OBJECT__HPP


#include "Andromeda/Space/Light/LightTypes.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"
#include "Object.hpp"


namespace Andromeda::Space
{
	class LightObject
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