#pragma once

#include <SpringEngine/Core/Asset.hpp>

namespace SE
{
	class AssetsManager
	{
	public:
		AssetsManager();
		~AssetsManager();

		uint32_t registerAsset(Asset* asset);

	public:
		std::forward_list<std::unique_ptr<Asset>> m_registeredAssets;
	};
}