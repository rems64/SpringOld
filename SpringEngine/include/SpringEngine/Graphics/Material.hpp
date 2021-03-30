#pragma once

#include <SpringEngine/core.hpp>
#include <vector>

namespace SE
{
	class Shader;
	class Texture;
	class SE_API Material
	{
	public:
		Material();
		~Material();

		inline Shader* getShader() { return m_shader; };
		Texture* getTexture(unsigned int id);
	private:
		Shader* m_shader;
		std::vector<Texture*> m_textures;
	};
}