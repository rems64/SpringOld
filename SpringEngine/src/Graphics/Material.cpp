#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Graphics/Texture.hpp>
#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	Material::Material()
	{
	}

	Material::~Material()
	{
	}

	Texture* Material::getTexture(unsigned int id)
	{
		if (m_textures.size() >= id)
			return m_textures[id];
		else
			return Application::get().getDataManager()->getDefaultTexture()
	}
}