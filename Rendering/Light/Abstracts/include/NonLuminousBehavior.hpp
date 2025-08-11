#ifndef RENDERING__NON_LUMINOUS_BEHAVIOR_HPP
#define RENDERING__NON_LUMINOUS_BEHAVIOR_HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../Interfaces/include/ILightBehavior.hpp"
#include "../../../Materials/include/Materials.hpp"



namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API NonLuminousBehavior
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
}


#endif // RENDERING__NON_LUMINOUS_BEHAVIOR_HPP