#pragma once

#include <SpringEngine/Core/SpringObject.hpp>

#include <SpringEngine/Core/Vector3.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API Component : public SpringObject
	{
	public:
		Component();
		~Component() = default;

		virtual inline bool getVisibility() { return m_isVisible; };
		virtual void setVisibility(bool newVisibility) { m_isVisible = newVisibility; };

		
		Vector3<float> getPosition() { return m_position; };
		void setPosition(Vector3<float> newPosition) { m_position = newPosition; };

		Vector3<float> getScale() { return m_scale; };
		void setScale(Vector3<float> newScale) { m_scale= newScale; };

		Vector3<float> getRotation() { return m_rotation; };
		void setRotation(Vector3<float> newRotation) { m_rotation = newRotation; };

	private:
		bool m_isVisible;

		Vector3<float> m_position;
		Vector3<float> m_scale;
		Vector3<float> m_rotation;
	};
}