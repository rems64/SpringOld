#pragma once

#include "../core.hpp"
#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/Core/CameraComponent.hpp>
#include <SpringEngine/Core/LightComponent.hpp>

namespace SE
{
	class Component;
	class Actor;
	class Event;
	class CameraComponent;
	class RenderedComponent;
	class DataManager;
	class SE_API Scene : public SpringObject
	{
	friend DataManager;
	public:
		Scene();
		virtual ~Scene();

		friend std::ostream& operator<<(std::ostream& os, Scene& scene);
		friend std::istream& operator>>(std::istream& is, Scene& scene);

		void onEvent(Event& ev);
		void update(double deltaSeconds, CameraComponent* cam);

		bool addComponentToScene(Component* component);

		std::vector<Actor*> importFBX(const char* path);
		int registerActor(Actor* actor);
		void unregisterActor(Actor* actor);
		std::vector<Actor*>* getRegisteredActors() { return &m_registeredActors; };

		void registerRenderedComponent(RenderedComponent* component, bool front=false);
		void unregisterRenderedComponent(RenderedComponent* component);

		void setCurrentCamera(CameraComponent* cam) { m_currentCamera = cam; };
		CameraComponent* getCurrentCamera() { return m_currentCamera; };

		std::vector<LightComponent*>* getLights() { return &m_lightsList; };
		void registerLight(LightComponent* light) { m_lightsList.push_back(light); };
		void unregisterLight(LightComponent* light);

		void clear();
	private:
		std::vector<Actor*> m_registeredActors;
		std::vector<RenderedComponent*> m_renderingList;
		std::vector<LightComponent*> m_lightsList;
		glm::mat4 m_projection;
		CameraComponent* m_currentCamera;
	};
}