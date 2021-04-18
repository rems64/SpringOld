#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API SpringObject
	{
	public:
		SpringObject();
		virtual ~SpringObject();

		virtual const char* getName() { return m_name; };
		virtual void setName(const char* name) { m_name = name; };
	private:
		const char* m_name;
	};
}