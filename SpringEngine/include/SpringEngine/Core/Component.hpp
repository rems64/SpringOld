#pragma once

#include <vector>

#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API Component : public SpringObject
	{
	public:
		Component();
		Component(const Component& src);
		~Component() = default;
		
		Component& operator=(Component other);

		virtual inline bool getVisibility() { return m_isVisible; };
		virtual void setVisibility(bool newVisibility) { m_isVisible = newVisibility; };

		
		virtual Vector3<float> getPosition() { return m_position; };
		virtual void setPosition(Vector3<float> newPosition) { m_position = newPosition; };

		virtual Vector3<float> getScale() { return m_scale; };
		virtual void setScale(Vector3<float> newScale) { m_scale= newScale; };

		virtual Vector3<float> getRotation() { return m_rotation; };
		virtual void setRotation(Vector3<float> newRotation) { m_rotation = newRotation; };

	private:
		bool m_isVisible;

		Vector3<float> m_position;
		Vector3<float> m_scale;
		Vector3<float> m_rotation;

		Component* m_parent;
		std::vector<Component> m_components;
	};
}