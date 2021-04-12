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
		m_currentScene->onEvent(event);

	}

	void WorldLayer::onUpdate(double deltaTime)
	{
		//Renderer::renderSceneElement(&m_element);
		m_currentScene->update(deltaTime);
		Renderer::beginSceneDraw(m_currentScene.get());
		int nbrDrawCalls = Renderer::endSceneDraw();
		
		SE_CORE_TRACE("Rendered scene with {0} draw calls", nbrDrawCalls);
	}

	void WorldLayer::onImGuiRender()
	{
	}
}