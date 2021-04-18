#pragma once

#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API Actor : public SpringObject
	{
	public:
		Actor();
		virtual ~Actor();

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

		virtual void tick(double deltaSeconds);
		virtual void drawCall();

	private:
		std::vector<ActorComponent*> m_components;
	};
}