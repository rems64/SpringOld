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

	std::vector<Actor*> Scene::importFBX(const char* path)
	{
		SE_PROFILE_FUNCTION();
		std::vector<MeshImportInfo> list = Application::get().getDataManager()->loadFBX(path);
		std::vector<Actor*> actors;
		Actor* actor = new Actor();
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (list[i].id >= 0)
			{
				Mesh* mesh = Application::get().getDataManager()->getRegisteredDataBlock<Mesh>(list[i].id);
				MeshComponent* meshComponent = new MeshComponent(actor->getRoot(), mesh);
				actor->addComponent<MeshComponent>(meshComponent);
				registerRenderedComponent(meshComponent);
			}
		}
		registerActor(actor);
		actors.push_back(actor);
		return actors;
	}

	int Scene::registerActor(Actor* actor)
	{
		m_registeredActors.push_back(actor);
		actor->setScene(this);
		return m_registeredActors.size()-1;
	}

	void Scene::onEvent(Event& ev)
	{
		SE_PROFILE_FUNCTION();
	}

	void Scene::update(double deltaSeconds, CameraComponent* cam)
	{
		SE_PROFILE_FUNCTION();
		for (std::vector<Actor*>::iterator actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
			(*actor)->tick(deltaSeconds);
			//(*actor)->drawCall();
		}
		SE::Renderer::beginSceneDraw(cam);
		for (auto drawable : m_renderingList)
		{
			drawable->drawCall();
		}
		SE::Renderer::endSceneDraw();
		//int nbrDrawCalls = SE::Renderer::endSceneDraw();
	}

	void Scene::registerRenderedComponent(RenderedComponent* component, bool front)
	{
		if (front)
		{
			m_renderingList.push_back(component);
		}
		else
		{
			m_renderingList.insert(m_renderingList.begin(), component);
		}
	}

	void Scene::unregisterRenderedComponent(RenderedComponent* componentToUnregister)
	{
		for (std::vector<RenderedComponent*>::iterator component = m_renderingList.begin(); component != m_renderingList.end(); component++)
		{
			if (*component == componentToUnregister)
			{
				m_renderingList.erase(component);
				break;
			}
		}
	}
}