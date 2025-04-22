#ifndef SPACE__SPHERE__HPP
#define SPACE__SPHERE__HPP


#include "ObjectTypes.hpp"
#include "ObjectBase.hpp"


namespace Andromeda
{
	namespace Space
	{
		class Sphere : public ObjectBase
		{
		public:
			Sphere();
			~Sphere();

			// Getters
			double GetRadius() const;

		private:
			float m_radius;

		};
	}
}


#endif // SPACE__SPHERE__HPP