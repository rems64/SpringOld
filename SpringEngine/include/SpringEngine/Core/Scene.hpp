#pragma once


#include "../core.hpp"
#include <SpringEngine/Core/CameraComponent.hpp>

namespace SE
{
	class Component;
	class Actor;
	class Event;
	class SE_API Scene
	{
	public:
		Scene();
		~Scene();


		void onEvent(Event& ev);
		void update(double deltaSeconds);

		bool addComponentToScene(Component* component);

		void importFBX(const char* path);
		bool registerActor(Actor* actor);
		std::vector<Actor*>* getRegisteredActors() { return &m_registeredActors; };
		CameraComponent* getMainCamera();
	private:
		std::vector<Actor*> m_registeredActors;
		glm::mat4 m_projection;
	};
}