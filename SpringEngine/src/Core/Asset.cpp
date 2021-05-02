#include <SpringEngine/Core/Asset.hpp>

namespace SE
{
	Asset::Asset() : m_dataBlock(nullptr), m_previewTexture(nullptr)
	{
	}

	Asset::Asset(DataBlock* dataBlock) : m_dataBlock(dataBlock), m_previewTexture(new Texture())
	{
		m_previewTexture->loadPNG("ressources/defaultPreview.png", 0, false);
	}

	Asset::~Asset()
	{
	}
}