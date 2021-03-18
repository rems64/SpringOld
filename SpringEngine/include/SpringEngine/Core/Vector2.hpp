#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	SE_API;
	template <typename T>
	class Vector2
	{
	public:
		Vector2() : m_x(0), m_y(0) {};
		Vector2(T x, T y) : m_x(x), m_y(y) {};
		template <typename U>
		Vector2(const Vector2<U>& src) : m_x(static_cast<T>(src.m_x)), m_y(static_cast<T>(src.m_y)) {};

		~Vector2()
		{
		};

		inline T x() const { return m_x; };
		inline T y() const { return m_y; };

	private:
		T m_x;
		T m_y;
	};

	template <typename T>
	inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x() + right.x(), left.y() + right.y());
	};

	template <typename T>
	inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.m_x += right.m_x;
		left.m_y += right.m_y;

		return left;
	}

	template <typename T>
	inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector3<T>(left.m_x - right.m_x, left.m_y - right.m_y, left.m_z - right.m_z);
	}

	template <typename T>
	inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.m_x -= right.m_x;
		left.m_y -= right.m_y;

		return left;
	}

	template <typename T>
	inline Vector2<T> operator *(const T left, const Vector2<T>& right)
	{
		return Vector2<T>(left * right.m_x, left * right.m_y);
	}

	template <typename T>
	inline Vector2<T> operator *(const Vector2<T>& left, const T right)
	{
		return Vector2<T>(left.m_x * right, left.m_y * right);
	}

	template <typename T>
	inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.m_x == right.m_x) && (left.m_y == left.m_y)
	}

	template <typename T>
	inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.m_x != right.m_x) || (left.m_y != left.m_y)
	}
	//template <typename T>
	//inline T dot(const SE::Vector3<T> left, const SE::Vector3<T>& right)
	//{
	//	return static_cast<T>(left.x()*right.x() + left.y()*right.y() + left.z()*right.z());
	//}

	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;

	typedef Vector2<float> Vector2f;

	typedef Vector2<long> Vector2l;
	typedef Vector2<unsigned long> Vector2ul;
}