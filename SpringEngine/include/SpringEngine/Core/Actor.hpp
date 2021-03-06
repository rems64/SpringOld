#pragma once

#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Events/Event.hpp>

namespace SE
{
	class ActorComponent;
	class SceneComponent;
	class DataManager;
	class Scene;
	class SE_API Actor : public SpringObject
	{
	public:
		Actor();
		virtual ~Actor();

		friend class DataManager;

		virtual void onEvent(Event& ev);

		template<typename T>
		void addComponent(T* component)
		{
			m_rootComponent->addComponent<T>(component);
			component->setOwner(m_rootComponent);
		}

		template<class T>
		T* getComponent(unsigned long index)
		{
			//return static_cast<T*>(m_components[index]);
			return m_rootComponent->getComponent<T>(index);
		}

		uint32_t getComponentCount();

		SceneComponent* getRoot() { return m_rootComponent; };

		virtual void editorUpdate(double deltaSeconds);
		virtual void update(double deltaSeconds);
		virtual void drawCall();

		virtual void setScene(Scene* scene) { m_scene = scene; };
		virtual Scene* getScene() { return m_scene; };

	protected:
		Scene* m_scene;
		SceneComponent* m_rootComponent;
		bool isPendingKill;
	};
}