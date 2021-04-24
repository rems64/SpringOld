#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/SpringObject.hpp>

namespace SE
{
	class Actor;
	class ActorComponent : public SpringObject
	{
	public:
		ActorComponent();
		ActorComponent(ActorComponent* owner);
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

		void removeComponent(ActorComponent* componentToRemove)
		{
			for (std::vector<ActorComponent*>::iterator component = m_components.begin(); component!=m_components.end();)
			{
				if (*component == componentToRemove)
				{
					m_components.erase(component);
					break;
				}
				else
				{
					component++;
				}
			}
		}

		virtual void postDestroy() {};

		uint32_t getComponentCount() { return m_components.size(); };
		std::vector<ActorComponent*>* getComponents() { return &m_components; };

		virtual void tick(double deltaSeconds) {
			for (auto component : m_components)
			{
				component->tick(deltaSeconds);
			};
		};

		virtual ActorComponent* getOwner() { return m_owner; };
		void setOwner(ActorComponent* owner) { m_owner = owner; };

		virtual void destroy();
	protected:
		ActorComponent* m_owner;
		std::vector<ActorComponent*> m_components;
	};
}