#include <SpringEngine/Core/Application.hpp>

SE::Application* SE::Application::s_instance = nullptr;

SE::Application::Application(std::string name) : m_windows(), m_name(name), m_appRunning(true), m_windowsNbr(0), m_frameRate(60), m_dataManager(new DataManager())
{
	SE::Log::init();
	SE_CORE_WARN("Application \"{0}\" started", name);
	if (s_instance!=nullptr)
		SE_CORE_ERROR("Application has already been created");
	s_instance = this;
	init();

	glfwWindowHint(GLFW_SAMPLES, 16);
	SE::Window* win = new SE::Window(name.c_str());
	win->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	m_windows.push_back(win);
	m_windowsNbr++;

	win->makeContextCurrent();
	win->setVSync(true);

	unsigned int glewInitResult = glewInit();
	if (glewInitResult)
	{
		SE_CORE_CRITICAL("An error occured while initilizing glew : {}", (GLenum)glewInitResult);
		abort;
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_worldLayer = new WorldLayer();
	s_instance->pushLayer(m_worldLayer);

	m_imGuiLayer = new ImGuiLayer();
	s_instance->pushOverlay(m_imGuiLayer);
}

SE::Application::Application(const SE::Application& src) : m_windows(src.m_windows), m_appRunning(src.m_appRunning), m_windowsNbr(src.m_windowsNbr), m_imGuiLayer(src.m_imGuiLayer), m_dataManager(src.m_dataManager)
{
}

SE::Application::~Application()
{
	m_layerStack.~LayerStack();
	glfwTerminate();
}

void SE::Application::init()
{
	if (!glfwInit())
	{
		SE_CORE_CRITICAL("An error occured while initilizing GLFW");
	}

}

int SE::Application::mainLoop()
{
	m_loopStart = std::chrono::high_resolution_clock::now();
	m_loopEnd = std::chrono::high_resolution_clock::now();
	m_deltaTime = m_loopEnd - m_loopStart;

	while (m_appRunning)
	{
		frame();
	}
	SE_INFO("Stopping application");
	return 0;
}

void SE::Application::frame()
{
	std::vector<SE::Window*>::iterator windowIterator = m_windows.begin();
	m_loopStart = std::chrono::high_resolution_clock::now();
	(**windowIterator).makeContextCurrent();
	(**windowIterator).swapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (Layer* layer : m_layerStack)
		layer->onUpdate(m_deltaTime.count());

	m_imGuiLayer->begin();
	{
		for (Layer* layer : m_layerStack)
			layer->onImGuiRender();
	}
	m_imGuiLayer->end();


	// Events
	glfwPollEvents();

	m_loopEnd = std::chrono::high_resolution_clock::now();
	m_deltaTime = m_loopEnd - m_loopStart;
	m_deltaSeconds = m_deltaTime.count() / 1000.;
	m_frameRate = 1 / m_deltaSeconds;
}

SE::Window& SE::Application::getMainWindow()
{
	return *m_windows[0];
}

void SE::Application::onEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowCloseEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResizeEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowMoveEvent>(std::bind(&Application::onWindowMoveEvent, this, std::placeholders::_1));

	for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
	{
		if (event.handled)
			break;
		(*it)->onEvent(event);
	}
}

void SE::Application::pushLayer(Layer* layer)
{
	m_layerStack.pushLayer(layer);
	layer->onAttach();
}

void SE::Application::pushOverlay(Layer* layer)
{
	m_layerStack.pushOverlay(layer);
	layer->onAttach();
}

bool SE::Application::onWindowCloseEvent(WindowCloseEvent& event)
{
	Window* win = event.getWindow();
	unsigned int concernedIndex=0;
	for (unsigned int i = 0; i < m_windows.size(); i++)
	{
		if (m_windows[i] == win)
		{
			concernedIndex = i;
			break;
		}
	}
	SE_CORE_INFO("Handling closing of the window with id {}", concernedIndex);
	m_appRunning = false;
	//m_windows[concernedIndex]->~Window();
	//m_windows.erase(m_windows.begin() + concernedIndex);
	//if (m_windows.empty())
	//{
	//}
	return true;
}

bool SE::Application::onWindowResizeEvent(WindowResizeEvent& event)
{
	//event.getWindow()->
	frame();
	return true;
}

bool SE::Application::onWindowMoveEvent(WindowMoveEvent& event)
{
	//frame();
	return true;
}

double SE::Application::getFPS()
{
	return m_frameRate;
}
