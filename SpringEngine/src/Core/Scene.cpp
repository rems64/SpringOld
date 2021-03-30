#include <SpringEngine/Core/Scene.hpp>

#include <memory>

namespace SE
{
	Scene::Scene() : m_viewCamera(), m_components()
	{
	}

	Scene::~Scene()
	{
		//for (auto i = 0; i < m_components.size(); i++)
		//{
		//	delete m_components[i];
		//}
	}

	bool Scene::addComponentToScene(Component* component)
	{
		m_components.push_back(std::shared_ptr<Component>(component));
		return true;
	}
}