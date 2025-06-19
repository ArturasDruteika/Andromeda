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
		public:
			NonLuminousBehavior();
			NonLuminousBehavior(
				float shininess,
				float specularStrength,
				float diffuseStrength
			);
			~NonLuminousBehavior();

			// Getters
			float GetShininess() const;
			float GetSpecularStrength() const;
			float GetDiffuseStrength() const;
			// Setters
			void SetShininess(float shininess);
			void SetSpecularStrength(float specularStrength);
			void SetDiffuseStrength(float diffuseStrength);

		private:
			float m_shininess;
			float m_specularStrength;
			float m_diffuseStrength;
		};
	}
}


#endif // RENDERING__NON_LUMINOUS_BEHAVIOR_HPP