#ifndef RENDERING__NON_LUMINOUS_BEHAVIOR_HPP
#define RENDERING__NON_LUMINOUS_BEHAVIOR_HPP


#include "pch.hpp"
#include "ILightBehavior.hpp"
#include "../../Materials/include/Materials.hpp"



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
				const std::string& name,
				const Math::Vec3& ambient,
				const Math::Vec3& specular,
				const Math::Vec3& diffuse
			);
			NonLuminousBehavior(const Material& material);
			~NonLuminousBehavior();

			// Getters
			float GetShininess() const;
			std::string GetName() const;
			Math::Vec3 GetAmbient() const;
			Math::Vec3 GetSpecular() const;
			Math::Vec3 GetDiffuse() const;
			// Setters
			void SetShininess(float shininess);
			void SetName(const std::string& name);
			void SetAmbient(const Math::Vec3& ambient);
			void SetSpecular(const Math::Vec3& specular);
			void SetDiffuse(const Math::Vec3& diffuse);

		private:
			Material m_material;
		};
	}
}


#endif // RENDERING__NON_LUMINOUS_BEHAVIOR_HPP