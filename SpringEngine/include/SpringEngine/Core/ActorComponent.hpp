#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/SpringObject.hpp>

namespace SE
{
	class ActorComponent : public SpringObject
	{
	public:
		ActorComponent();
		virtual ~ActorComponent();

		template<typename T>
		void addComponent(T* component)
		{
			m_components.push_back(component);
		}

		template<class T>
		T* getComponent(unsigned long index)
		{
			return static_cast<T*>(m_components[index]);
		}

		uint32_t getComponentCount() { return m_components.size(); };

	private:
		std::vector<ActorComponent*> m_components;
	};
}