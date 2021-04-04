#include <SpringEngine/Layers/ImGuiLayer.hpp>

#include <SpringEngine/Core/Application.hpp>

SE::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
}


void SE::ImGuiLayer::onAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnabled;

	//ImGui::StyleColorsDark();

	Application& app = Application::get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.getMainWindow().getNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	//const char* v = (const char*)glGetIntegerv(GL_VERSION);
	SE_CORE_INFO("ImGui layer running on renderer {0}", glGetString(GL_VERSION));
	ImGui_ImplOpenGL3_Init("#version 410");
	//ImGui_ImplOpenGL3_Init();

	auto font_default = io.Fonts->AddFontDefault();
}

void SE::ImGuiLayer::onDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void SE::ImGuiLayer::onEvent(Event& event)
{
	if (m_blockEvents)
	{
		ImGuiIO& io = ImGui::GetIO();
		event.handled |= event.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		event.handled |= event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}
}

void SE::ImGuiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void SE::ImGuiLayer::end()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::get();
	io.DisplaySize = ImVec2((float)app.getMainWindow().getSize().x, (float)app.getMainWindow().getSize().y);

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
