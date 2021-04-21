#pragma once


#include "../core.hpp"
#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	class Component;
	class Actor;
	class Event;
	class CameraComponent;
	class RenderedComponent;
	class SE_API Scene : public SpringObject
	{
	public:
		Scene();
		virtual ~Scene();


		void onEvent(Event& ev);
		void update(double deltaSeconds, CameraComponent* cam);

		bool addComponentToScene(Component* component);

		std::vector<Actor*> importFBX(const char* path);
		int registerActor(Actor* actor);
		std::vector<Actor*>* getRegisteredActors() { return &m_registeredActors; };

		void registerRenderedComponent(RenderedComponent* component, bool front=false);
		void unregisterRenderedComponent(RenderedComponent* component);

		void setCurrentCamera(CameraComponent* cam) { m_currentCamera = cam; };
		CameraComponent* getCurrentCamera() { return m_currentCamera; };
	private:
		std::vector<Actor*> m_registeredActors;
		std::vector<RenderedComponent*> m_renderingList;
		glm::mat4 m_projection;
		CameraComponent* m_currentCamera;
	};
}