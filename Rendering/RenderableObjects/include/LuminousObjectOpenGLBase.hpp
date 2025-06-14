#ifndef RENDERING__LUMINOUS_OBJECT_OPENGL_BASE__HPP
#define RENDERING__LUMINOUS_OBJECT_OPENGL_BASE__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class LuminousObjectOpenGLBase
		{
		public:
			LuminousObjectOpenGLBase();
			LuminousObjectOpenGLBase(float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
			~LuminousObjectOpenGLBase();

			// Getters
			float GetAttenuationConstant() const;
			float GetAttenuationLinear() const;
			float GetAttenuationQuadratic() const;
			// Setters
			void SetAttenuationConstant(float attenuationConstant);
			void SetAttenuationLinear(float attenuationLinear);
			void SetAttenuationQuadratic(float attenuationQuadratic);

		private:
			float m_attenuationConstant;
			float m_attenuationLinear;
			float m_attenuationQuadratic;
		};
	}
}


#endif // RENDERING__LUMINOUS_OBJECT_OPENGL_BASE__HPP