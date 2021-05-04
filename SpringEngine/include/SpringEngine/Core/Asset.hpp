#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/DataBlock.hpp>
#include <SpringEngine/Graphics/Texture.hpp>

namespace SE
{
	class SE_API Asset
	{
	public:
		Asset();
		Asset(DataBlock* dataBlock);
		~Asset();

	private:
		DataBlock* m_dataBlock;
		Texture* m_previewTexture;
	};
}