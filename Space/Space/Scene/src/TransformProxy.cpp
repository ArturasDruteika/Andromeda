#include "../include/TransformProxy.hpp"


namespace Andromeda::Space
{
	TransformProxy::TransformProxy(Transformable* transformable)
		: m_transformable{ transformable }
	{
	}

	TransformProxy::~TransformProxy() = default;

	ITransformable* TransformProxy::GetTransformable() const
	{
		return m_transformable;
	}
}