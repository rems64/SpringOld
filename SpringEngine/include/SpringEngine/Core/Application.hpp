#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <SpringEngine/Core/Vector2.hpp>
#include <SpringEngine/Core/Window.hpp>
#include <SpringEngine/Core/Input.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Core/LayerStack.hpp>
#include <SpringEngine/Layers/ImGuiLayer.hpp>
#include <SpringEngine/Layers/WorldLayer.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/DataManager.hpp>
#include <SpringEngine/Core/InputManager.hpp>
#include <SpringEngine/Core/Scene.hpp>

#include<SpringEngine/core.hpp>


namespace SE
{
	class SE_API Application
	{
	public:
		Application() = default;
		Application(std::string name);
		Application(const SE::Application& src);
		virtual ~Application();

		void init();
		int mainLoop();
		void frame();

		void closeApplication();

		Window& getMainWindow();
		inline DataManager* getDataManager() { return m_dataManager; };
		inline ImGuiContext* getImguiContext() { return ImGui::GetCurrentContext(); };
		inline ImGuiLayer* getImGuiLayer() { return m_imGuiLayer; };
		inline InputManager* getInputManager() { return m_inputManager; };

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		bool onWindowCloseEvent(WindowCloseEvent& event);
		bool onWindowResizeEvent(WindowResizeEvent& event);
		bool onWindowMoveEvent(WindowMoveEvent& event);

		Vector2d getMousePosition();

		double getFPS();
		double getDeltaSeconds() { return m_deltaSeconds; };

		static Application& get() { return *s_instance; }
	private:
		static Application* s_instance;
		std::vector<SE::Window*> m_windows;
		unsigned int m_windowsNbr;
		std::string m_name;
		bool m_appRunning;
		double m_frameRate;
		double m_deltaSeconds;

		LayerStack m_layerStack;
		ImGuiLayer* m_imGuiLayer;
		WorldLayer* m_worldLayer;
		DataManager* m_dataManager;
		InputManager* m_inputManager;
		
		std::chrono::high_resolution_clock::time_point m_loopStart;
		std::chrono::high_resolution_clock::time_point m_loopEnd;
		std::chrono::duration<double, std::milli> m_deltaTime;
	};

	Application* CreateApplication();
};

#define Input Application::get()->getInputManager()