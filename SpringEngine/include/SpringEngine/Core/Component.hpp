#pragma once

#include <vector>

#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/core.hpp>

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>

namespace SE
{
	class SE_API Component
	{
	public:
		Component();
		Component(const Component& src);
		virtual ~Component() = default;
		
		Component& operator=(Component other);

		virtual inline bool getVisibility() { return m_isVisible; };
		virtual void setVisibility(bool newVisibility) { m_isVisible = newVisibility; updateModelMatrix(); };

		
		virtual Vector3<float> getPosition() { return m_position; };
		virtual void setPosition(Vector3<float> newPosition) { m_position = newPosition; updateModelMatrix(); };
		virtual void addPosition(Vector3<float> positionOffset) { m_position += positionOffset; updateModelMatrix(); };

		virtual Vector3<float> getScale() { return m_scale; };
		virtual void setScale(Vector3<float> newScale) { m_scale= newScale; updateModelMatrix(); };

		virtual Vector3<float> getRotation() { return m_rotation; };
		virtual void setRotation(Vector3<float> newRotation) { m_rotation = newRotation; updateModelMatrix(); };
		virtual void addRotation(Vector3<float> offsetRotation) { m_rotation += offsetRotation; updateModelMatrix();  };

		glm::mat4* getModelMatrix() { return &m_modelMatrix; };
		void updateModelMatrix();
	protected:
		bool m_isVisible;

		Vector3<float> m_position;
		Vector3<float> m_scale;
		Vector3<float> m_rotation;

		glm::mat4 m_modelMatrix;

		Component* m_parent;
		std::vector<Component> m_components;
	};
}