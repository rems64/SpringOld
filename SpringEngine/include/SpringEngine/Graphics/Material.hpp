#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <vector>

namespace SE
{
	class Texture;
	enum class SE_PROPERTY_TYPE
	{
		NONE,
		COLOR,
		TEXTURE
	};
	class SE_API Material
	{
	public:
		Material();
		Material(const Material& src);
		~Material();

		void bind();
		void unbind();

		void updateShaderUniforms();

		inline Shader* getShader() { return &m_shader; };
		Texture* getTexture(unsigned int id);

		void setDiffuseColor(float r, float g, float b);
	private:
		Shader m_shader;
		std::vector<Texture*> m_textures;
		enum SE_PROPERTY_TYPE m_diffuseType;
		Vector3f m_diffuseColor;
	};
}