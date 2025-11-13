#ifndef PHYSICAL_PROPERTIES__NON_LUMINOUS_BEHAVIOR_HPP
#define PHYSICAL_PROPERTIES__NON_LUMINOUS_BEHAVIOR_HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../Interfaces/include/ILightBehavior.hpp"
#include "../../../Materials/include/Materials.hpp"



namespace Andromeda::PhysicalProperties
{
	class PHYSICAL_PROPERTIES_API NonLuminousBehavior
		: public ILightBehavior
	{
	public:
		NonLuminousBehavior();
		NonLuminousBehavior(const Material& material);
		~NonLuminousBehavior();

		// Getters
		Material GetMaterial();
		// Setters
		void SetMaterial(const Material& material);

	private:
		Material m_material;
	};
}


#endif // PHYSICAL_PROPERTIES__NON_LUMINOUS_BEHAVIOR_HPP