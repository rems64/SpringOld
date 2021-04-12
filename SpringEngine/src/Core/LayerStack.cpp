#include <SpringEngine/Core/LayerStack.hpp>
#include "..\..\include\SpringEngine\Core\LayerStack.hpp"


SE::LayerStack::~LayerStack()
{
	for (SE::Layer* layer : m_layers)
	{
		layer->onDetach();
		delete layer;
	}
}

void SE::LayerStack::pushLayer(SE::Layer* layer)
{
	SE_PROFILE_FUNCTION();
	m_layers.emplace(m_layers.begin() + m_layerStackIndex, layer);
	m_layerStackIndex++;
}

void SE::LayerStack::popLayer(SE::Layer* layer)
{
	SE_PROFILE_FUNCTION();
	std::vector<SE::Layer*>::iterator it = std::find(m_layers.begin(), m_layers.begin() + m_layerStackIndex, layer);
	if (it != m_layers.begin() + m_layerStackIndex)
	{
		layer->onDetach();
		m_layers.erase(it);
		m_layerStackIndex--;
	}
}

void SE::LayerStack::pushOverlay(SE::Layer* layer)
{
	m_layers.emplace_back(layer);
}

void SE::LayerStack::popOverlay(SE::Layer* layer)
{
	SE_PROFILE_FUNCTION();
	std::vector<SE::Layer*>::iterator it = std::find(m_layers.begin() + m_layerStackIndex, m_layers.end(), layer);
	if (it != m_layers.end())
	{
		layer->onDetach();
		m_layers.erase(it);
	}
}
