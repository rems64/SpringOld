#include <SpringEngine/Core/AssetsManager.hpp>

namespace SE
{
	AssetsManager::AssetsManager()
	{

	}

	AssetsManager::~AssetsManager()
	{

	}

	uint32_t AssetsManager::registerAsset(Asset* asset)
	{
		m_registeredAssets.push_front(std::unique_ptr<Asset>(asset));
		SE_CORE_INFO("Asset registered");
		return m_registeredAssets.max_size();
	}
}