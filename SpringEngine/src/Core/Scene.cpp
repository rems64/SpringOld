#include <SpringEngine/Core/Scene.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/MeshComponent.hpp>

namespace SE
{
	Scene::Scene() : m_registeredActors()
	{
	}

	Scene::~Scene()
	{
		for (auto i = 0; i < m_registeredActors.size(); i++)
		{
			delete m_registeredActors[i];
		}
	}

	void Scene::importFBX(const char* path)
	{
		SE_PROFILE_FUNCTION();
		std::vector<unsigned long> list = Application::get().getDataManager()->loadFBX(path);
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (list[i] >= 0)
			{
				Mesh* mesh = Application::get().getDataManager()->getRegisteredDataBlock<Mesh>(list[i]);
				Actor* actor = new Actor();
				MeshComponent* meshComponent = new MeshComponent(mesh);
				actor->addComponent<MeshComponent>(meshComponent);
				registerActor(actor);
			}
		}
	}

	bool Scene::registerActor(Actor* actor)
	{
		m_registeredActors.push_back(actor);
		return true;
	}

	void Scene::onEvent(Event& ev)
	{
		SE_PROFILE_FUNCTION();
	}

	void Scene::update(double deltaSeconds)
	{
		SE_PROFILE_FUNCTION();
		for (std::vector<Actor*>::iterator actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
			(*actor)->tick(deltaSeconds);
		}
	}

	CameraComponent* Scene::getMainCamera()
	{
		/*for (auto actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
		}*/
		return nullptr;
	}
}