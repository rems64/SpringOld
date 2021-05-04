#include <SpringEngine/Layers/WorldLayer.hpp>

#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Actor.hpp>

namespace SE
{
	WorldLayer::WorldLayer() : Layer("World layer"), m_currentScene(std::make_shared<Scene>())
	{
	}

	void WorldLayer::onAttach()
	{
		Actor* cameraActor = new Actor();
		CameraComponent* cam = new CameraComponent(cameraActor->getRoot());
		//cameraActor->getRoot()->setLocation(Vector3f(4.0, 4.0, 6.0));
		cam->setLocation(Vector3f(4.0, 4.0, 6.0));
		m_currentScene->registerActor(cameraActor);
		m_currentScene->setCurrentCamera(cam);
	}

	void WorldLayer::onDetach()
	{
	}

	void WorldLayer::onEvent(Event& event)
	{
		if (event.getEventType() != SE::EventType::MouseMoved)
		{
			SE_CORE_INFO("Event on world layer {0}", event.toString());
		}
		m_currentScene->onEvent(event);

	}

	void WorldLayer::onUpdate(double deltaTime)
	{
		//Renderer::renderSceneElement(&m_element);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TO UPDATE in order to accord with the new standalone camera style

		Renderer::beginSceneDraw(m_currentScene->getCurrentCamera(), m_currentScene.get());
		m_currentScene->update(deltaTime, m_currentScene->getCurrentCamera());
		int nbrDrawCalls = Renderer::endSceneDraw();
		
		//SE_CORE_TRACE("Rendered scene with {0} draw calls", nbrDrawCalls);
	}

	void WorldLayer::onImGuiRender()
	{
	}
}