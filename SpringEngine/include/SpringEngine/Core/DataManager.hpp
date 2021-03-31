#pragma once

#include <vector>
#include <memory>
#include <map>

#include <SpringEngine/core.hpp>

namespace SE
{
	class Scene;
	class Texture;
	class Material;

	class SE_API DataManager
	{
	public:
		DataManager();
		~DataManager();

		const void parseObj(const char* path);
		bool loadFBX(const char* path, Scene* scene);
		
		// Textures
		Texture* getDefaultTexture();
		int loadTexture(const char* path);
	private:
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::map<unsigned int, std::shared_ptr<Material>> m_materials;
	};
}