#include <SpringEngine/Core/Window.hpp>

SE::Window::Window() : m_window(nullptr), m_data(this, "Default window", 0, 0, 1280, 720, true)
{
	constructWindow();
}

SE::Window::Window(const SE::Window& src) : m_window(src.m_window), m_data(src.m_data)
{
	SE_CORE_TRACE("Copying window with title {}", m_data.m_title);
}

SE::Window::Window(const char* title) : m_window(nullptr), m_data(this, title, 0, 0, 1280, 720, true)
{
	constructWindow();
}

SE::Window::Window(int width, int height, int xpos, int ypos, const char* title) : m_window(nullptr), m_data(this, title, xpos, ypos, width, height, true)
{
	constructWindow();
}

SE::Window::~Window()
{
	SE_CORE_TRACE("Destroying window");
	glfwDestroyWindow(m_window);
}

GLFWwindow* SE::Window::getWindow()
{
	return m_window;
}

void SE::Window::constructWindow()
{
	SE_PROFILE_FUNCTION();
	m_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title, NULL, NULL);

	glfwSetWindowUserPointer(m_window, &m_data);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* win)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			WindowCloseEvent event(data.m_owner);
			data.m_eventCallback(event);
		}
	);

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			data.m_width = width;
			data.m_height = height;
			glViewport(0, 0, width, height);
			WindowResizeEvent event(data.m_owner, width, height);
			data.m_eventCallback(event);
		}
	);

	glfwSetWindowPosCallback(m_window, [](GLFWwindow* win, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			WindowMoveEvent event(data.m_owner, x, y);
			data.m_eventCallback(event);
		}
	);
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			MouseMove event(x, y);
			data.m_eventCallback(event);
		}
	);
	
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* win, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			double x, y;
			glfwGetCursorPos(win, &x, &y);
			if (action == GLFW_PRESS)
			{
				MousePressed event(button, action, mods, x, y);
				data.m_eventCallback(event);
			}
			else if (action == GLFW_RELEASE)
			{
				MouseReleased event(button, action, mods, x, y);
				data.m_eventCallback(event);
			}
		}
	);

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key);
					data.m_eventCallback(event);
					break;
				}
			}
		});
}

void SE::Window::setWindow(GLFWwindow* window)
{
	m_window = window;
}

void SE::Window::setTitle(const char* title)
{
	m_data.m_title = title;
	glfwSetWindowTitle(m_window, title);
}

const char* SE::Window::getTitle()
{
	return m_data.m_title;
}

void SE::Window::setSize(unsigned int width, unsigned int height)
{
	glfwSetWindowSize(m_window, width, height);
	m_data.m_width = width;
	m_data.m_height = height;
}

glm::vec2 SE::Window::getSize()
{
	int tmpWidth, tmpHeight;
	glfwGetWindowSize(m_window, &tmpWidth, &tmpHeight);
	return glm::vec2(tmpWidth, tmpHeight);
}

void SE::Window::setPosition(int x, int y)
{
	m_data.m_x = x;
	m_data.m_y = y;
	glfwSetWindowPos(m_window, x, y);
}

glm::vec2 SE::Window::getPosition()
{
	return glm::vec2(m_data.m_x, m_data.m_y);
}

void SE::Window::setVSync(bool set)
{
	m_data.m_VSync = set;
	glfwSwapInterval(set ? 1 : 0);
}

bool SE::Window::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void SE::Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void SE::Window::makeContextCurrent()
{
	glfwMakeContextCurrent(m_window);
}