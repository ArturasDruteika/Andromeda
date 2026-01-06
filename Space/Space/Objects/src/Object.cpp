#include "../include/Object.hpp"


namespace Andromeda::Space
{
	std::atomic<int> Object::s_nextId{ 0 };

	Object::Object()
		: m_isActive{ false }
		, m_id{ s_nextId++ }
		, m_name{}
	{
	}

	Object::~Object() = default;

	bool Object::IsActive() const
	{
		return m_isActive;
	}

	int Object::GetID() const
	{
		return m_id;
	}

	const std::string& Object::GetName() const
	{
		return m_name;
	}

	void Object::Active(bool active)
	{
		m_isActive = active;
	}

	void Object::SetName(const std::string& name)
	{
		m_name = name;
	}
}
