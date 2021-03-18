#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API DataManager
	{
	public:
		DataManager();
		~DataManager();

		const char* openFile(const char* filepath);
	private:

	};
}