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

		friend class DataManager;
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

		size_t getComponentCount() { return m_components.size(); };
		std::vector<ActorComponent*>* getComponents() { return &m_components; };

		virtual void editorUpdate(double deltaSeconds) {
			for (auto component : m_components)
			{
				component->editorUpdate(deltaSeconds);
			};
		};

		virtual void update(double deltaSeconds) {
			for (auto component : m_components)
			{
				component->update(deltaSeconds);
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