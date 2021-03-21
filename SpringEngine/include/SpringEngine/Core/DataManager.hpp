#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	class Scene;

	class SE_API DataManager
	{
	public:
		DataManager();
		~DataManager();

		const void parseObj(const char* path);
		bool loadFBX(const char* path, Scene scene);
	private:

	};
}