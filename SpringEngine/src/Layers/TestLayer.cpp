#include <SpringEngine/Layers/TestLayer.hpp>

SE::TestLayer::TestLayer(const char* name) : SE::Layer(name)
{
	SE_CORE_INFO("Spawning layer {}", m_name);
}

void SE::TestLayer::onAttach()
{
	SE_CORE_INFO("Attaching layer {}", m_name);
}

void SE::TestLayer::onDetach()
{
	SE_CORE_INFO("Detaching layer {}", m_name);
}

void SE::TestLayer::onEvent(Event& event)
{
	std::cout << m_name << " | " << event << std::endl;
}

void SE::TestLayer::onImGuiRender()
{
	ImGui::Begin("Stats");
	ImGui::Text("Stats");
	ImGui::End();
}
