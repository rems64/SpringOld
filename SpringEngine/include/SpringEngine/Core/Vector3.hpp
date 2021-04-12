#pragma once

namespace SE
{
	template <typename T>
	class Vector3
	{
	public:
		Vector3() : m_x(0), m_y(0), m_z(0) {};
		Vector3(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {};
		template <typename U>
		Vector3(const Vector3<U>& src) : m_x(static_cast<T>(src.m_x)), m_y(static_cast<T>(src.m_y)), m_z(static_cast<T>(src.m_z)) {};
		
		~Vector3()
		{
		};

		inline T x() const { return m_x; };
		inline T y() const { return m_y; };
		inline T z() const { return m_z; };

		inline void x(T value) { m_x = value; };
		inline void y(T value) { m_y = value; };
		inline void z(T value) { m_z = value; };

		inline glm::vec3 getGlm()					// Temporary solution
		{
			return glm::vec3(m_x, m_y, m_z);
		}
	protected:
		T m_x;
		T m_y;
		T m_z;
	};

	template <typename T>
	inline Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3<T>(left.x() + right.x(), left.y() + right.y(), left.z() + right.z());
	};

	template <typename T>
	inline Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.x(left.x() + right.x());
		left.y(left.y() + right.y());
		left.z(left.z() + right.z());

		return left;
	}

	template <typename T>
	inline Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3<T>(left.m_x - right.m_x, left.m_y - right.m_y, left.m_z - right.m_z);
	}

	template <typename T>
	inline Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.m_x -= right.m_x;
		left.m_y -= right.m_y;
		left.m_z -= right.m_z;

		return left;
	}

	template <typename T>
	inline Vector3<T> operator *(const T left, const Vector3<T>& right)
	{
		return Vector3<T>(left * right.m_x, left * right.m_y, left * right.m_z);
	}

	template <typename T>
	inline Vector3<T> operator *(const Vector3<T>& left, const T right)
	{
		return Vector3<T>(left.m_x * right, left.m_y * right, left.m_z * right);
	}

	template <typename T>
	inline bool operator ==(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.m_x==right.m_x) && (left.m_y==left.m_y) && (left.m_z==right.m_z)
	}

	template <typename T>
	inline bool operator !=(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.m_x != right.m_x) || (left.m_y != left.m_y) || (left.m_z != right.m_z)
	}
	//template <typename T>
	//inline T dot(const SE::Vector3<T> left, const SE::Vector3<T>& right)
	//{
	//	return static_cast<T>(left.x()*right.x() + left.y()*right.y() + left.z()*right.z());
	//}

	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;

	typedef Vector3<float> Vector3f;

	typedef Vector3<long> Vector3l;
	typedef Vector3<unsigned long> Vector3ul;
}