#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Vector3.hpp>

namespace SE
{
	class Scene;
	class Texture;
	class Material;
	class Mesh;
	class DataBlock;


	struct MeshImportInfo
	{
		const char *name;
		unsigned int id;
	};

	enum class SceneLoadMode : uint32_t
	{
		OVERRIDE = 0,
		ADD = 1,
		SUBTRACT = 2
	};
	class SE_API DataManager
	{
	public:
		DataManager();
		~DataManager();


		std::vector<MeshImportInfo> loadFBX(const char* path);
		

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

		bool saveScene(Scene* scene, const char* path);
		bool loadScene(Scene* scene, const char* path, enum SceneLoadMode mode = SceneLoadMode::OVERRIDE);
		template <typename T>
		nlohmann::json vec3ToJson(Vector3<T> vec)
		{
			nlohmann::json j = { {"x", vec.x()}, { "y", vec.y() }, { "z", vec.z() } };
			return j;
		}

		template <typename T>
		Vector3<T> jsonToVec3(nlohmann::json json)
		{
			return Vector3<T>(json.at("x").get<T>(), json.at("y").get<T>(), json.at("z").get<T>());
		}
	private:
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::map<unsigned long, DataBlock*> m_dataBlocks;
	};
}