#ifndef API__SPACE__SCENE__TRANSFORM_PROXY__HPP
#define API__SPACE__SCENE__TRANSFORM_PROXY__HPP


#include "../../Transformations/include/Transformable.hpp"
#include "Andromeda/Space/Scene/ITransformProxy.hpp"


namespace Andromeda::Space
{
	class TransformProxy
		: public ITransformProxy
	{
	public:
		explicit TransformProxy(Transformable* transformable);
		~TransformProxy();

		ITransformable* GetTransformable() const override;

	private:
		Transformable* m_transformable;
	};
}

#endif // API__SPACE__SCENE__TRANSFORM_PROXY__HPP
