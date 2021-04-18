#include <SpringEngine/Layers/DebugUILayer.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <GLFW/glfw3.h>

SE::DebugUILayer::DebugUILayer(const char* name) : Layer(name), m_lastHistogramUpdate(0)
{
	memset(m_frameRateOverTime, 0, sizeof(m_frameRateOverTime));
}

void SE::DebugUILayer::onAttach()
{
	SE_PROFILE_FUNCTION();
	m_glVersion = glGetString(GL_VERSION);
	SE_CORE_INFO("DebugUI layer running on renderer {0}", m_glVersion);
}

void SE::DebugUILayer::onDetach()
{
	SE_PROFILE_FUNCTION();
	//SE_CORE_INFO("Detaching Debug UI layer {}", m_name);
}

void SE::DebugUILayer::onEvent(Event& event)
{

}

template <typename T>
void left_rotate_by_one(T arr[], int n)
{

	/* Shift operation to the left */
	int temp = arr[0];
	int i;
	for (i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];
	arr[i] = temp;
}

void SE::DebugUILayer::onImGuiRender()
{
	SE_PROFILE_FUNCTION();
	double currentTime = glfwGetTime();
	if (currentTime - m_lastHistogramUpdate >= (5.f/SE_DEBUGUI_HISTOGRAM_COUNT))
	{

		left_rotate_by_one(m_frameRateOverTime, SE_DEBUGUI_HISTOGRAM_COUNT);
		m_frameRateOverTime[SE_DEBUGUI_HISTOGRAM_COUNT-1] = Application::get().getFPS();

		m_lastHistogramUpdate = currentTime;
	}

	ImGui::Begin("Stats");
	ImGui::Text("Framerate");
	ImGui::PlotLines("Frame Times", m_frameRateOverTime, SE_DEBUGUI_HISTOGRAM_COUNT, 0, 0, 0);
	ImGui::Text((const char*)(m_glVersion));
	ImGui::Text("%u draw calls", SE::Renderer::getSceneDrawCalls());
	ImGui::End();
}
