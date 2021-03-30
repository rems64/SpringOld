#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <SpringEngine/Core/Window.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Core/LayerStack.hpp>
#include <SpringEngine/Layers/ImGuiLayer.hpp>
#include <SpringEngine/Layers/WorldLayer.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/SceneElement.hpp>
#include <SpringEngine/Core/DataManager.hpp>
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

		Window& getMainWindow();
		inline DataManager* getDataManager() { return m_dataManager; };
		inline Scene* getCurrentScene() { return m_worldLayer->getScene(); }

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		bool onWindowCloseEvent(WindowCloseEvent& event);

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
	};

	Application* CreateApplication();
};