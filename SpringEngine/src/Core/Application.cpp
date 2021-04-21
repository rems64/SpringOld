#include <SpringEngine/Core/Application.hpp>


namespace SE
{
	Application* Application::s_instance = nullptr;

	Application::Application(std::string name) : m_windows(), m_name(name), m_appRunning(true), m_windowsNbr(0), m_frameRate(60), m_dataManager(new DataManager())
	{
		Log::init();
		SE_CORE_WARN("Application \"{0}\" started", name);
		if (s_instance != nullptr)
			SE_CORE_ERROR("Application has already been created");
		s_instance = this;
		init();

		Instrumentor::get().beginSession("Application");
		SE_PROFILE_SCOPE("Initialisaing app");

		Window* win = new Window(name.c_str());
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

		//glfwWindowHint(GLFW_SAMPLES, 16);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		//m_worldLayer = new WorldLayer();
		//s_instance->pushLayer(m_worldLayer);

		m_imGuiLayer = new ImGuiLayer();
		s_instance->pushOverlay(m_imGuiLayer);
	}

	Application::Application(const Application& src) : m_windows(src.m_windows), m_appRunning(src.m_appRunning), m_windowsNbr(src.m_windowsNbr), m_imGuiLayer(src.m_imGuiLayer), m_dataManager(src.m_dataManager)
	{
	}

	Application::~Application()
	{
		m_layerStack.~LayerStack();
		glfwTerminate();
		Instrumentor::get().endSession();
	}

	void Application::init()
	{
		if (!glfwInit())
		{
			SE_CORE_CRITICAL("An error occured while initilizing GLFW");
		}

	}

	int Application::mainLoop()
	{
		SE_PROFILE_FUNCTION();
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

	void Application::frame()
	{
		SE_PROFILE_FUNCTION();
		std::vector<Window*>::iterator windowIterator = m_windows.begin();
		m_loopStart = std::chrono::high_resolution_clock::now();
		(**windowIterator).makeContextCurrent();
		(**windowIterator).swapBuffers();

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

	void Application::closeApplication()
	{
		for (auto i = m_windows.begin(); i != m_windows.end(); i++)
		{
			(*i)->close();
		}
	}

	Window& Application::getMainWindow()
	{
		return *m_windows[0];
	}

	void Application::onEvent(Event& event)
	{
		SE_PROFILE_FUNCTION();
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

	void Application::pushLayer(Layer* layer)
	{
		SE_PROFILE_FUNCTION();
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& event)
	{
		Window* win = event.getWindow();
		unsigned int concernedIndex = 0;
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

	bool Application::onWindowResizeEvent(WindowResizeEvent& event)
	{
		//event.getWindow()->
		frame();
		return true;
	}

	bool Application::onWindowMoveEvent(WindowMoveEvent& event)
	{
		//frame();
		return true;
	}

	double Application::getFPS()
	{
		return m_frameRate;
	}

	bool Application::isKeyPressed(const KeyCode key)
	{
		auto state = glfwGetKey((GLFWwindow*)getMainWindow().getNativeWindow(), static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Application::isMouseButtonDown(const MouseCode button)
	{
		auto state = glfwGetMouseButton((GLFWwindow*)getMainWindow().getNativeWindow(), static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	Vector2d Application::getMousePosition()
	{
		double x, y;
		glfwGetCursorPos((GLFWwindow*)getMainWindow().getNativeWindow(), &x, &y);
		return Vector2d(x, y);
	}
}