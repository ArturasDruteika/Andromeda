#include "../include/KeyEvents.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		KeyPressEvent::KeyPressEvent()
			: m_key(0)
			, m_action(0)
		{
		}

		KeyPressEvent::~KeyPressEvent()
		{
		}

		int KeyPressEvent::GetKey() const
		{
			return m_key;
		}

		int KeyPressEvent::GetAction() const
		{
			return m_action;
		}
	}
}