#pragma once

#include <GLFW/glfw3.h>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Events/WindowEvents.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API Window
	{
	public:
		Window();
		Window(const SE::Window& src);
		Window(const char* title);
		Window(int width, int height, int xpos, int ypos, const char* title);
		~Window();

		GLFWwindow* getWindow();
		void setWindow(GLFWwindow* window);
		void setTitle(const char* title);
		const char* getTitle();
		
		void setSize(unsigned int width, unsigned int height);
		glm::vec2 getSize();
		void setPosition(int x, int y);
		glm::vec2 getPosition();

		float getRatio() { return (float)m_data.m_width / (float)m_data.m_height; };

		void setVSync(bool set);

		bool shouldClose();
		void swapBuffers();

		void makeContextCurrent();

		void constructWindow();

		void* getNativeWindow() { return m_window; };

		using EventCallbackFunction = std::function<void(SE::Event&)>;
		inline void setEventCallback(const EventCallbackFunction& clbk) { m_data.m_eventCallback = clbk; };
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			const char* m_title;
			unsigned int m_x;
			unsigned int m_y;
			unsigned int m_width;
			unsigned int m_height;
			bool m_VSync;

			Window* m_owner;

			EventCallbackFunction m_eventCallback;

			WindowData(Window* owner, const char* title, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool vsync) : m_owner(owner), m_title(title), m_x(x), m_y(y), m_width(width), m_height(height), m_VSync(vsync) {};
			WindowData(const WindowData& src) : m_owner(src.m_owner), m_title(src.m_title), m_x(src.m_x), m_y(src.m_y), m_width(src.m_width), m_height(src.m_height), m_VSync(src.m_VSync), m_eventCallback(src.m_eventCallback) {};
		};

		WindowData m_data;
	};
}