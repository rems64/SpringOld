#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API SpringObject
	{
	public:
		SpringObject();
		virtual ~SpringObject();

		virtual const char* getName() const { return m_name.c_str(); };
		virtual std::string& getNameStr() { return m_name; };
		virtual void setName(const char* name);
	protected:
		std::string m_name;
	};
}