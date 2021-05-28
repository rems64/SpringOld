#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Graphics/Shader.hpp>
#include <SpringEngine/Core/Vector3.hpp>


#define SE_MAX_PROPERTY_LENGTH 20

namespace SE
{
	class Texture;
	enum class SE_API SE_MATERIAL_PROPERTY_TYPE
	{
		NONE,
		COLOR,
		TEXTURE
	};
	enum class SE_API SE_MATERIAL_PROPERTY_NAME
	{
		NONE,
		DIFFUSE,
		SPECULAR,
		METALLIC,
		ROUGHNESS,
		NORMAL
	};

	struct SE_API MaterialProperty
	{
		enum SE_MATERIAL_PROPERTY_NAME m_name;
		enum SE_MATERIAL_PROPERTY_TYPE m_type;
		Texture* m_texture;
		Vector3<float> m_color;
		MaterialProperty(SE_MATERIAL_PROPERTY_NAME name, SE_MATERIAL_PROPERTY_TYPE type, Texture* texture) : m_name(name), m_type(type), m_color(), m_texture(texture)
		{
			if (type != SE_MATERIAL_PROPERTY_TYPE::TEXTURE)
			{
				SE_CORE_WARN("Can't assign texture property ({0}) on color", (int)name);
			}
		}
		MaterialProperty(SE_MATERIAL_PROPERTY_NAME name, SE_MATERIAL_PROPERTY_TYPE type, Vector3<float> color) : m_name(name), m_type(type), m_color(color), m_texture()
		{
			if (type != SE_MATERIAL_PROPERTY_TYPE::COLOR)
			{
				SE_CORE_WARN("Can't assign color property ({0}) on texture", (int)name);
			}
		}
	};
	class SE_API Material
	{
	public:
		Material();
		Material(const char* path);
		Material(const Material& src);
		~Material();

		void bind() const;
		void unbind() const;

		void updateShaderUniforms();

		void pickShader(bool normalMapped);

		/** Set the scene projection matrix.
		 * This should be called from the renderer before the draw call. 
		 * [WARNING] The shader HAS TO be bound before calling this function
		 * @param projection The glm 4x4 projection matrix.
		 *   In the futur this will be replaced by SE::Mat4
		 */
		void setProjectionMatrix(glm::mat4 projection) const;
		void setViewMatrix(glm::mat4 view) const;
		void setModelMatrix(glm::mat4 model) const;

		inline Shader* getShader() const { return m_shader; };
		MaterialProperty* getProperty(SE_MATERIAL_PROPERTY_NAME name);

		bool registerProperty(MaterialProperty property);

		void bindTextures() const;
		void unbindTextures() const;

		Shader* getShader() { return m_shader; };
	private:
		Shader* m_shader;
		std::vector<MaterialProperty> m_properties;
		Vector3f m_diffuseColor;
	};
}