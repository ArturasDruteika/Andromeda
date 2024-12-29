#include "../include/Event.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		Event::Event()
		{
		}

		Event::~Event()
		{
		}

		std::string Event::ToString() const
		{
			return GetName();
		}

		bool Event::IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	}
}

