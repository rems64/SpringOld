#include <SpringEditor/EditorLayer.hpp>

namespace SpringEditor
{
	EditorLayer::EditorLayer() : SE::Layer("Editor layer"), m_viewport(), m_framebuffer(), m_currentScene(std::make_shared<SE::Scene>()), m_editorCamera()
	{

	}

	EditorLayer::~EditorLayer()
	{
		delete m_framebuffer;
		delete m_tmpImage;
		delete m_editorCamera;
	}

	void EditorLayer::onAttach()
	{
		m_framebuffer = new SE::Framebuffer(SE::Vector2ui(640, 360));
		m_currentScene->importFBX("ressources/axis.fbx");
		m_tmpImage = new SE::Texture();
		m_tmpImage->loadPNG("C:/Users/rfaye/OneDrive/Images/buf2.png", 4, true);
		m_editorCamera = new SE::CameraComponent();
		m_editorCamera->setLocation(SE::Vector3f(4., 4., 4.));

		m_temp = 0.f;

		SE::Mesh* meshInstance = new SE::Mesh();
		SE::MeshComponent* mesh = new SE::MeshComponent(meshInstance);
		mesh->setName("Child");
		m_currentScene->getRegisteredActors()->at(0)->getComponent<SE::ActorComponent>(0)->setName("Mesh");
		m_currentScene->getRegisteredActors()->at(0)->getComponent<SE::ActorComponent>(0)->addComponent<SE::MeshComponent>(mesh);
		m_currentScene->getRegisteredActors()->at(0)->getComponent<SE::ActorComponent>(0)->getComponent<SE::MeshComponent>(0)->addComponent<SE::ActorComponent>(m_currentScene->getRegisteredActors()->at(0)->getComponent<SE::MeshComponent>(0));
	}

	void EditorLayer::onEvent(SE::Event& event)
	{
		if (event.getEventType() != SE::EventType::MouseMoved)
		{
			SE_CORE_INFO("Event on editor layer {0}", event.toString());
		}
		m_currentScene->onEvent(event);
	}

	void EditorLayer::onUpdate(double deltaTime)
	{
		SE_PROFILE_FUNCTION();
		m_temp += deltaTime;

		m_currentScene->getRegisteredActors()[0].at(0)->getComponent<SE::MeshComponent>(0)->setRotation(SE::Vector3f(0.0, 0.0, m_temp * 0.002));

		if (((uint32_t)m_framebuffer->getWidth() != (uint32_t)m_viewport.x() || (uint32_t)m_framebuffer->getHeight() != (uint32_t)m_viewport.y()) && (m_viewport.x()!=0 && m_viewport.y()!=0))
		{
			m_framebuffer->resize((uint32_t)m_viewport.x(), (uint32_t)m_viewport.y());
			m_editorCamera->setRatio(m_viewport.x() / m_viewport.y());
			//SE_CORE_TRACE("width: {} height: {}", m_viewport.x(), m_viewport.y());
			//SE_CORE_TRACE("{} {} {} {}", m_framebuffer->getWidth(), m_viewport.x(), m_framebuffer->getHeight(), m_viewport.y());
		}

		m_framebuffer->bind();
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering stuff
		m_currentScene->update(deltaTime, m_editorCamera);
		//SE_CORE_TRACE("{} draw calls", nbrDrawCalls);

		m_framebuffer->unbind();
	}

	void EditorLayer::onImGuiRender()
	{
		SE_PROFILE_FUNCTION()
		ImGui::SetCurrentContext(SE::Application::get().getImguiContext());

        static ImGuiID dockspaceID = 0;
        bool active = true;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;


        static bool dockspaceOpen = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar(3);
        
        dockspaceID = ImGui::GetID("EditorDockspace");
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
		ImGui::PopStyleVar();
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					SE_CORE_INFO("New");
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					SE_CORE_INFO("Open");
				}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
				{
					SE_CORE_INFO("Save as");
				}

				if (ImGui::MenuItem("Exit"))
				{
					SE::Application::get().closeApplication();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (ImGui::Begin("Viewport"))
		{
			uint32_t bufferId = m_framebuffer->getColorAttachmentRendererID();
			m_viewport.x(ImGui::GetContentRegionAvail().x);
			m_viewport.y(ImGui::GetContentRegionAvail().y);
			ImGui::Image(reinterpret_cast<void*>(bufferId), ImVec2{ m_viewport.x(), m_viewport.y() }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			//glBlitFramebuffer(bufferId, 0, 640, 480, 0, 0, 640, 480, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}
        ImGui::End();
		ImGui::PopStyleVar();

		if (ImGui::Begin("Assets"))
		{
			ImGui::TextUnformatted("Assets");
		}
		ImGui::End(); // Assets
		
		if (ImGui::Begin("Outliner"))
		{
			ImGuiTreeNodeFlags flags = ((true) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
			std::vector<SE::Actor*>* actors = m_currentScene->getRegisteredActors();
			uint32_t index = 0;
			for (std::vector<SE::Actor*>::iterator it = actors->begin(); it != actors->end(); it++, index++)
			{
				bool opened = ImGui::TreeNodeEx((void*)index, flags, (*it)->getName());
				if (opened)
				{
					m_actorComponentRecursiveDepth = 0;
					m_actorComponentRecursiveStack.clear();
					for (uint32_t j = 0; j < (*it)->getComponentCount(); j++)
					{
						drawActorComponentInList((*it)->getComponent<SE::ActorComponent>(j));
					}
					ImGui::TreePop();
				}
			}
		}
		ImGui::End(); // Outliner

		if (ImGui::Begin("Properties"))
		{
			ImGui::TextUnformatted("Properties");
		}
		ImGui::End();// Properties


		ImGui::End(); // Dockspace
	};

	void EditorLayer::drawActorComponentInList(SE::ActorComponent* component)
	{
		SE_PROFILE_FUNCTION()
		if (m_actorComponentRecursiveDepth > 10)
		{
			return;
		}
		if ((std::find(m_actorComponentRecursiveStack.begin(), m_actorComponentRecursiveStack.end(), component)!= m_actorComponentRecursiveStack.end()) && (true))
		{
			ImGuiTreeNodeFlags flags = ((true) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
			bool opened = ImGui::TreeNodeEx((void*)0, flags, "Recursion error");
			if (opened)
			{
				ImGui::TreePop();
			}
			return;
		}
		m_actorComponentRecursiveStack.push_back(component);
		m_actorComponentRecursiveDepth++;
		uint32_t count = component->getComponentCount();
		ImGuiTreeNodeFlags flags = ((true) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | (count == 1 ? 0 : ImGuiTreeNodeFlags_Leaf);
		bool opened = ImGui::TreeNodeEx((void*)0, flags, component->getName());
		if (opened)
		{
			for (uint32_t j = 0; j < count; j++)
			{
				EditorLayer::drawActorComponentInList(component->getComponent<SE::ActorComponent>(j));
			}
			ImGui::TreePop();
		}
	}
}