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

	Material::Material(const char* path) : m_shader(new Shader(path)), m_properties()
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

	void Material::pickShader(bool normalMapped)
	{
		if (normalMapped)
		{
			delete m_shader;
			m_shader = new Shader("../../../../ISUFlightSimulator/ressources/basic_deferred_object.glsl");
			m_shader->compile();
		}
	}

	uint32_t getTextureIndexFromName(SE_MATERIAL_PROPERTY_NAME name)
	{
		switch (name)
		{
			case (SE_MATERIAL_PROPERTY_NAME::DIFFUSE):
				return 0;
			case (SE_MATERIAL_PROPERTY_NAME::NORMAL):
				return 1;
			case (SE_MATERIAL_PROPERTY_NAME::SPECULAR):
				return 2;
			case (SE_MATERIAL_PROPERTY_NAME::METALLIC):
				return 3;
			case (SE_MATERIAL_PROPERTY_NAME::ROUGHNESS):
				return 4;
		}
	}

	void Material::updateShaderUniforms()
	{
		bind();
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
			case(SE_MATERIAL_PROPERTY_NAME::NORMAL):
				if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
				{
					strcpy(location, "u_normal_texture");
				}
				else if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::COLOR)
				{
					strcpy(location, "u_normal_color");
				}
				break;
			case(SE_MATERIAL_PROPERTY_NAME::SPECULAR):
				strcpy(location, "u_specularTexture");
				break;
			case(SE_MATERIAL_PROPERTY_NAME::METALLIC):
				strcpy(location, "u_metallicTexture");
				break;
			case(SE_MATERIAL_PROPERTY_NAME::ROUGHNESS):
				strcpy(location, "u_roughnessTexture");
				break;
			}
			if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
			{
				m_shader->bind();
				m_shader->setUniform1i(location, getTextureIndexFromName(m_properties[i].m_name));
			}
			else if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::COLOR)
			{
				m_shader->bind();
				m_shader->setUniform3f(location, m_properties[i].m_color);
			}
			else
			{
				SE_CORE_WARN("No property type was given");
			}
		}
	}

	void Material::setProjectionMatrix(glm::mat4 matrix) const			// WARNING : Has to be bound
	{
		m_shader->setUniformMat4f("u_projection", matrix);
	}

	void Material::setViewMatrix(glm::mat4 matrix) const			// WARNING : Has to be bound
	{
		m_shader->setUniformMat4f("u_view", matrix);
	}

	void Material::setModelMatrix(glm::mat4 matrix) const			// WARNING : Has to be bound
	{
		m_shader->setUniformMat4f("u_model", matrix);
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
				m_properties[i].m_texture->bind(getTextureIndexFromName(m_properties[i].m_name));
			}
		}
	}

	void Material::unbindTextures() const
	{
		for (uint32_t i = 0; i < m_properties.size(); i++)
		{
			if (m_properties[i].m_type == SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
			{
				m_properties[i].m_texture->unbind();
			}
		}
	}
}