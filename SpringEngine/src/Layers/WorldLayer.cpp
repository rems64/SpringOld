#include <SpringEngine/Layers/WorldLayer.hpp>

#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	WorldLayer::WorldLayer() : Layer("World layer"), m_currentScene(std::make_shared<Scene>())
	{
	}

	void WorldLayer::onAttach()
	{
		m_framebuffer = new SE::Framebuffer(SE::Vector2ui(1920, 1080), {});

		Actor* cameraActor = new Actor();
		CameraComponent* cam = new CameraComponent(cameraActor->getRoot());
		//cameraActor->getRoot()->setLocation(Vector3f(4.0, 4.0, 6.0));
		cam->setLocation(Vector3f(-4.0, 8.0, 0.0));
		cam->setRotation(Vector3f(-1.057079632679, -1.57079632679, 0.0));
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
		m_viewport.x(SE::Application::get().getMainWindow().getSize().x);
		m_viewport.y(SE::Application::get().getMainWindow().getSize().y);
		if (((uint32_t)m_framebuffer->getWidth() != (uint32_t)m_viewport.x() || (uint32_t)m_framebuffer->getHeight() != (uint32_t)m_viewport.y()) && (m_viewport.x() != 0 && m_viewport.y() != 0))
		{
			m_framebuffer->resize((uint32_t)m_viewport.x(), (uint32_t)m_viewport.y());
			m_currentScene->getCurrentCamera()->setViewport(m_viewport.x(), m_viewport.y());
			m_currentScene->getCurrentCamera()->setRatio(m_viewport.x() / m_viewport.y());
			//SE_CORE_TRACE("Resize");
		}

		m_framebuffer->bind();

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer::beginSceneDraw(m_currentScene->getCurrentCamera(), m_currentScene.get());
		m_currentScene->update(deltaTime, m_currentScene->getCurrentCamera());
		Renderer::endSceneDraw();

		// Render to screen
		Renderer::renderToScreen(m_framebuffer);
		//m_framebuffer->unbind();
	}

	void WorldLayer::onImGuiRender()
	{
		Renderer::renderToScreen(m_framebuffer);
	}
}