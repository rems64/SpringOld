#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Vector2.hpp>

namespace SE
{
	template<typename T>
	class Box2D
	{
	public:
		Box2D() : m_min(), m_max() {};
		Box2D(Vector2<T> min, Vector2<T> max) : m_min(min), m_max(max) {};
		Box2D(T xmin, T ymin, T xmax, T ymax) : m_min(xmin, ymin), m_max(xmax, ymax) {};
		~Box2D() {};

		Vector2<T>& const getMin() { return m_min; };
		Vector2<T>& const getMax() { return m_max; };

	private:
		Vector2<T> m_min;
		Vector2<T> m_max;
	};
}