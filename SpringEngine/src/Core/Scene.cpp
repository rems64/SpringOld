#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	Scene::Scene() : m_components(), m_viewCamera()
	{
	}

	Scene::~Scene()
	{
	}

	bool Scene::addComponentToScene(Component& component)
	{
		m_components.push_back(component);
		return true;
	}
}