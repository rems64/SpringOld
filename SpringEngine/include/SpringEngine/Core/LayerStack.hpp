#pragma once

#include <vector>
#include <SpringEngine/Core/Layer.hpp>

#include "../core.hpp"

namespace SE
{
	class SE_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void pushLayer(SE::Layer* layer);
		void popLayer(SE::Layer* layer);

		void pushOverlay(SE::Layer* layer);
		void popOverlay(SE::Layer* layer);

		std::vector<SE::Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<SE::Layer*>::iterator end() { return m_layers.end(); }
		std::vector<SE::Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<SE::Layer*>::reverse_iterator rend() { return m_layers.rend(); }

		std::vector<SE::Layer*>::const_iterator begin() const { return m_layers.begin(); }
		std::vector<SE::Layer*>::const_iterator end()	const { return m_layers.end(); }
		std::vector<SE::Layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
		std::vector<SE::Layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }
	private:
		std::vector<SE::Layer*> m_layers;
		unsigned m_layerStackIndex = 0;
	};
}