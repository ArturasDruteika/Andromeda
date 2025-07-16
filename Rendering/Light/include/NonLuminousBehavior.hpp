#ifndef RENDERING__NON_LUMINOUS_BEHAVIOR_HPP
#define RENDERING__NON_LUMINOUS_BEHAVIOR_HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "ILightBehavior.hpp"
#include "../../Materials/include/Materials.hpp"



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