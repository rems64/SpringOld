#include <SpringEngine/Core/DataManager.hpp>

#include <ofbx.h>
#include <iostream>

#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/Scene.hpp>


namespace SE
{
	DataManager::DataManager()
	{
	}

	DataManager::~DataManager()
	{
	}

	const void DataManager::parseObj(const char* path)
	{
	}

	bool DataManager::loadFBX(const char* path, Scene* sceneRef)
	{
		ofbx::IScene* scene = nullptr;

		FILE* fp = fopen(path, "rb");

		if (!fp) return false;

		fseek(fp, 0, SEEK_END);
		long file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		auto* content = new ofbx::u8[file_size];
		fread(content, 1, file_size, fp);

		scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
		if (!scene) {
			SE_CORE_ERROR("An error occured in reading FBX ({0}) : {1}", path, ofbx::getError());
			return false;
		}
		SE_CORE_INFO("FBX ({0}) loaded. It contains {1} meshes", path, scene->getMeshCount());
		for (unsigned int mesh = 0; mesh < scene->getMeshCount(); mesh++)
		{
			SE_CORE_INFO("Mesh with index ({0}) is named {1}", mesh, scene->getMesh(mesh)->name);
			for (unsigned int i=0; i < scene->getMesh(mesh)->getGeometry()->getVertexCount(); i++)
			{

			}
		}
	}
}