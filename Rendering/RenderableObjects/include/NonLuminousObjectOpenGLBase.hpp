#ifndef RENDERING__NON_LUMINOUS_OBJECT_OPENGL_BASE__HPP
#define RENDERING__NON_LUMINOUS_OBJECT_OPENGL_BASE__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class NonLuminousObjectOpenGLBase
		{	
		public:
			NonLuminousObjectOpenGLBase();
			NonLuminousObjectOpenGLBase(float shininess, float specularStrength, float diffuseStrength);
			~NonLuminousObjectOpenGLBase();

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


#endif // RENDERING__NON_LUMINOUS_OBJECT_OPENGL_BASE__HPP