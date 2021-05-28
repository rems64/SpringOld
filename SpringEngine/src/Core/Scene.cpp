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

	void Scene::unregisterActor(Actor* actorToUnregister)
	{
		for (std::vector<Actor*>::iterator actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
			if (*actor == actorToUnregister)
			{
				m_registeredActors.erase(actor);
				break;
			}
		}
	}

	void Scene::onEvent(Event& ev)
	{
		SE_PROFILE_FUNCTION();
		for (auto actor : m_registeredActors)
		{
			actor->onEvent(ev);
		}
	}

	void Scene::editorUpdate(double deltaSeconds, CameraComponent* cam)
	{
		SE_PROFILE_FUNCTION();
		for (std::vector<Actor*>::iterator actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
			(*actor)->editorUpdate(deltaSeconds);
		}
		SE::Renderer::beginSceneDraw(cam, this);
		uint32_t i = 0;
		for (auto drawable : m_renderingList)
		{
			SE::Renderer::setDebugIndex(i);
			drawable->drawCall();
			i++;
		}
		for (auto light : m_lightsList)
		{
			auto directionalLight = dynamic_cast<DirectionalLightComponent*>(light);
			if (directionalLight)
			{
				directionalLight->getFramebuffer()->bind();
				GLCall(glClear(GL_DEPTH_BUFFER_BIT));
				for (auto drawable : m_renderingList)
				{
					drawable->shadowPassCall(directionalLight);
				}
			}
		}
		SE::Renderer::endSceneDraw();
	}

	void Scene::update(double deltaSeconds, CameraComponent* cam)
	{
		SE_PROFILE_FUNCTION();
		for (std::vector<Actor*>::iterator actor = m_registeredActors.begin(); actor != m_registeredActors.end(); actor++)
		{
			(*actor)->update(deltaSeconds);
		}
		SE::Renderer::beginSceneDraw(cam, this);
		for (auto drawable : m_renderingList)
		{
			drawable->drawCall();
		}
		SE::Renderer::endSceneDraw();
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

	void Scene::unregisterLight(LightComponent* light)
	{
		for (std::vector<LightComponent*>::iterator component = m_lightsList.begin(); component != m_lightsList.end(); component++)
		{
			if (*component == light)
			{
				m_lightsList.erase(component);
				break;
			}
		}
	}
	std::ostream& operator<<(std::ostream& os, Scene& scene)
	{
		uint32_t nbr = 18;
		os.write((char*)scene.getNameStr().size(), sizeof(size_t));
		//os.write((char*)&scene.getNameStr(), scene.getNameStr().size());
		os.write((char*)&nbr, 2);
		return os;
	}

	std::istream& operator>>(std::istream& is, Scene& scene)
	{
		uint32_t size = 0;
		std::string a;
		uint32_t b = 0;
		is.read((char*)size, sizeof(size_t));
		//is.read((char*)&a, size);
		is.read((char*)&b, 2);
		return is;
	}

	void Scene::clear()
	{
		for (auto actor : m_registeredActors)
		{
			delete actor;
		}
		m_registeredActors.clear();
		m_renderingList.clear();
		m_lightsList.clear();
	}
}
