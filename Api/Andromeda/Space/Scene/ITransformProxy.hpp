#ifndef API__SCENE__I_TRANSFORM_PROXY__HPP
#define API__SCENE__I_TRANSFORM_PROXY__HPP


#include "../Transformations/ITransformable.hpp"


namespace Andromeda
{
	class ITransformProxy
		: public virtual ITransformable
	{
	public:
		~ITransformProxy() = default;

		virtual ITransformable* GetTransformable() const = 0;
	};
}


#endif // API__SCENE__I_TRANSFORM_PROXY__HPP