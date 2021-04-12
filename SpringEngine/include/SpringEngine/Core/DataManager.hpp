#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	class Scene;
	class Texture;
	class Material;
	class Mesh;
	class DataBlock;

	class SE_API DataManager
	{
	public:
		DataManager();
		~DataManager();

		std::vector<unsigned long> loadFBX(const char* path);
		

		// Textures
		Texture* getDefaultTexture();
		Texture* loadTexture(const char* path);

		template<class T>
		int registerDataBlock(T* dataBlock)
		{
			m_dataBlocks.insert(std::make_pair(m_dataBlocks.size(), dataBlock));
			return m_dataBlocks.size() - 1;
		}
		
		template<class T>
		T* getRegisteredDataBlock(unsigned long id)
		{
			return static_cast<T*>(m_dataBlocks.find(id)->second);
		}
	private:
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::map<unsigned long, DataBlock*> m_dataBlocks;
	};
}