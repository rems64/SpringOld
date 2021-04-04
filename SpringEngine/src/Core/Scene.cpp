#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	Scene::Scene() : m_viewCamera(new CameraComponent()), m_components()
	{
		m_viewCamera->setPosition(Vector3f(3, 3, 3));
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