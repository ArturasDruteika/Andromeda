#ifndef RENDERING__ABSTRACTS__LUMINOUS__HPP
#define RENDERING__ABSTRACTS__LUMINOUS__HPP


#include "Space/Light/Interfaces/include/ILightBehavior.hpp"


namespace Andromeda::Rendering
{
	class Luminous
	{
	public:
		Luminous();
		~Luminous();
		
		// Getters
		bool IsLuminous() const;
		Space::ILightBehavior* GetLightBehavior() const;
		// Setters
		void SetLuminousBehavior(Space::ILightBehavior* behavior);

	protected:
		bool m_luminous;
		Space::ILightBehavior* m_pILightBehavior;
	};
}


#endif // RENDERING__ABSTRACTS__LUMINOUS__HPP