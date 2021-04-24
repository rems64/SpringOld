#pragma once

#include <SpringEngine/Core/SpringObject.hpp>

namespace SE
{
	class SE_API DataBlock : public SpringObject
	{
	public:
		DataBlock();
		virtual ~DataBlock();

		virtual bool isValid() { return m_isValid; };
		virtual void setValid(bool valid) { m_isValid = valid; };

	protected:
		bool m_isValid;
	};
}