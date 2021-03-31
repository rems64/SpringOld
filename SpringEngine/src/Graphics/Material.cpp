#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Graphics/Texture.hpp>
#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	//Material::Material() : m_shader("ressources/basic_colored.glsl"), m_diffuseType(SE_PROPERTY_TYPE::COLOR), m_diffuseColor()
	Material::Material() : m_shader("../../../../ISUFlightSimulator/ressources/basic_colored.glsl"), m_diffuseType(SE_PROPERTY_TYPE::COLOR), m_diffuseColor()
	{
		m_shader.compile();
	}

	Material::Material(const Material& src) : m_diffuseColor(src.m_diffuseColor), m_diffuseType(src.m_diffuseType), m_shader(src.m_shader), m_textures(src.m_textures)
	{
	}

	Material::~Material()
	{
	}

	void Material::bind()
	{
		m_shader.bind();
	}

	void Material::unbind()
	{
		m_shader.unbind();
	}

	void Material::updateShaderUniforms()
	{
		m_shader.setUniform3f("u_diffuse_color", m_diffuseColor.x(), m_diffuseColor.y(), m_diffuseColor.z());
	}

	Texture* Material::getTexture(unsigned int id)
	{
		if (m_textures.size() >= id)
			return m_textures[id];
		else
			return Application::get().getDataManager()->getDefaultTexture();
	}

	void Material::setDiffuseColor(float r, float g, float b)
	{
		m_diffuseColor.x(r);
		m_diffuseColor.y(g);
		m_diffuseColor.z(b);
		return void();
	}
}