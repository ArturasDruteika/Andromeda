#ifndef SPACE__NON_LUMINOUS_BEHAVIOR_HPP
#define SPACE__NON_LUMINOUS_BEHAVIOR_HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "../../../Materials/include/Materials.hpp"
#include "Andromeda/Light/INonLuminousBehavior.hpp"


namespace Andromeda::Space
{
	class SPACE_API NonLuminousBehavior
		: public INonLuminousBehavior
	{
	public:
		NonLuminousBehavior();
		NonLuminousBehavior(const Material& material);
		~NonLuminousBehavior() override;

		// Getters
		const Material& GetMaterial() const override;
		// Setters
		void SetMaterial(const IMaterial& material) override;

	private:
		Material m_material;
	};
}


#endif // SPACE__NON_LUMINOUS_BEHAVIOR_HPP