#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Graphics/Texture.hpp>

namespace SE
{
	Material::Material() : m_shader(new Shader("../../../../ISUFlightSimulator/ressources/basic_colored.glsl")), m_properties()
	{
		m_shader->compile();
	}

	Material::Material(const Material& src) : m_diffuseColor(src.m_diffuseColor), m_properties(src.m_properties), m_shader(src.m_shader)
	{
	}

	Material::~Material()
	{
		delete m_shader;
	}

	void Material::bind() const
	{
		m_shader->bind();
	}

	void Material::unbind() const
	{
		m_shader->unbind();
	}

	void Material::updateShaderUniforms()
	{
		char location[SE_MAX_PROPERTY_LENGTH];
		for (uint32_t i = 0; i < m_properties.size(); i++)
		{
			switch (m_properties[i].m_name)
			{
			case(SE_MATERIAL_PROPERTY_NAME::NONE):
				SE_CORE_WARN("Property name doesn't exist");
				break;
			case(SE_MATERIAL_PROPERTY_NAME::DIFFUSE):
				if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
				{
					strcpy(location, "u_diffuse_texture");
				}
				else if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::COLOR)
				{
					strcpy(location, "u_diffuse_color");
				}
				break;
			case(SE_MATERIAL_PROPERTY_NAME::ROUGHNESS):
				strcpy(location, "u_roughness");
				break;
			}
			if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
			{
				m_shader->setUniform1i(location, 0);
			}
			else if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::COLOR)
			{
				m_shader->setUniform3f(location, m_properties[i].m_color);
			}
			else
			{
				SE_CORE_WARN("No property type was given");
			}
		}
	}

	void Material::setTransformMatrix(glm::mat4& matrix) const
	{
		m_shader->setUniformMat4f("u_projection", matrix);
	}

	MaterialProperty* Material::getProperty(SE_MATERIAL_PROPERTY_NAME name)
	{
		if (m_properties.size() > 0)
		{
			for (uint32_t i = 0; i < m_properties.size(); i++)
			{
				if (m_properties[i].m_name == name)
				{
					return &m_properties[i];
				}
			};
			SE_CORE_WARN("Property not found ({0})", (int)name);
			return nullptr;
		}
		else
		SE_CORE_WARN("There is no property in material");
		return nullptr;
	}

	bool Material::registerProperty(MaterialProperty property)
	{
		m_properties.emplace_back(property);
		return true;
	}

	void Material::bindTextures() const
	{
		for (uint32_t i = 0; i < m_properties.size(); i++)
		{
			if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
			{
				m_properties[i].m_texture->bind(0);
			}
		}
	}
}