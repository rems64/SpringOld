#include <SpringEngine/Core/SpringObject.hpp>


namespace SE
{
	SpringObject::SpringObject() : m_name("default name")
	{
	}

	SpringObject::~SpringObject()
	{
	}

	void SpringObject::setName(const char* name)
	{
		m_name = name;
	};
};