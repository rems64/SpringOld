#include <SpringEngine/Layers/WorldLayer.hpp>

#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	WorldLayer::WorldLayer() : Layer("World layer"), m_currentScene(std::make_shared<Scene>())
	{
	}

	void WorldLayer::onAttach()
	{
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
	}

	void WorldLayer::onUpdate(double deltaTime)
	{
		//Renderer::renderSceneElement(&m_element);
		Renderer::renderScene(m_currentScene.get(), deltaTime);
	}

	void WorldLayer::onImGuiRender()
	{
	}
}