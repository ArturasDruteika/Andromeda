#ifndef RENDERING__ABSTRACTS__LUMINOUS__HPP
#define RENDERING__ABSTRACTS__LUMINOUS__HPP


#include "ILightBehavior.hpp"


namespace Andromeda::Rendering
{
	class Luminous
	{
	public:
		Luminous();
		~Luminous();
		
		// Getters
		bool IsLuminous() const;
		PhysicalProperties::ILightBehavior* GetLightBehavior() const;
		// Setters
		void SetLuminousBehavior(PhysicalProperties::ILightBehavior* behavior);

	protected:
		bool m_luminous;
		PhysicalProperties::ILightBehavior* m_pILightBehavior;
	};
}


#endif // RENDERING__ABSTRACTS__LUMINOUS__HPP