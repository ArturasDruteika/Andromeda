#ifndef RENDERING__ABSTRACTS__LUMINOUS__HPP
#define RENDERING__ABSTRACTS__LUMINOUS__HPP

#include "../../../Light/include/ILightBehavior.hpp"


namespace Andromeda::Rendering
{
	class Luminous
	{
	public:
		Luminous();
		~Luminous();
		
		// Getters
		bool IsLuminous() const;
		ILightBehavior* GetLightBehavior() const;
		// Setters
		void SetLuminousBehavior(ILightBehavior* behavior);

	protected:
		bool m_luminous;
		ILightBehavior* m_pILightBehavior;
	};
}


#endif // RENDERING__ABSTRACTS__LUMINOUS__HPP