#include <SpringEditor/EditorLayer.hpp>
#include <SpringEngine/Core/Math.hpp>

namespace SpringEditor
{
	EditorLayer::EditorLayer() : SE::Layer("Editor layer"), m_viewport(), m_framebuffer(), m_currentScene(std::make_shared<SE::Scene>()), m_editorCamera(), m_guizmoOperation(ImGuizmo::TRANSLATE), m_selectedComponent(nullptr)
	{

	}

	EditorLayer::~EditorLayer()
	{
		delete m_framebuffer;
		delete m_editorCamera;
	}

	void EditorLayer::onAttach()
	{
		SE::Application::get().getMainWindow().setVSync(true);
		m_framebuffer = new SE::Framebuffer(SE::Vector2ui(1920, 1080));
		m_editorCamera = new SE::CameraComponent(nullptr);
		m_editorCamera->setLocation(SE::Vector3f(10.0, 10.0, 6.));
		m_currentScene->setCurrentCamera(m_editorCamera);


		SE::Actor* particleActor = new SE::Actor();
		SE::ParticleEmitterComponent* particEmitComp = new SE::ParticleEmitterComponent(particleActor->getRoot());
		particleActor->addComponent<SE::ParticleEmitterComponent>(particEmitComp);
		m_currentScene->registerActor(particleActor);
		m_currentScene->registerRenderedComponent(particEmitComp, true);
	}

	void EditorLayer::onEvent(SE::Event& event)
	{
		SE::EventDispatcher disp(event);
		disp.Dispatch<SE::KeyPressedEvent>(SE_BIND_EVENT(EditorLayer::onKeyPressedEvent));
		m_currentScene->onEvent(event);
	}

	bool EditorLayer::onKeyPressedEvent(SE::KeyPressedEvent& event)
	{
		switch (event.getKeyCode())
		{
			case SE::Key::D1:
				if (m_usingGuizmo)
				{
					if (m_guizmoOperation != ImGuizmo::TRANSLATE)
					{
						m_guizmoOperation = ImGuizmo::TRANSLATE;
					}
					else
					{
						m_usingGuizmo = false;
					}
				}
				else
				{
					m_guizmoOperation = ImGuizmo::TRANSLATE;
					m_usingGuizmo = true;
				}
				break;
			case SE::Key::D2:
				if (m_usingGuizmo)
				{
					if (m_guizmoOperation != ImGuizmo::ROTATE)
					{
						m_guizmoOperation = ImGuizmo::ROTATE;
					}
					else
					{
						m_usingGuizmo = false;
					}
				}
				else
				{
					m_guizmoOperation = ImGuizmo::ROTATE;
					m_usingGuizmo = true;
				}
				break;
			case SE::Key::D3:
				if (m_usingGuizmo)
				{
					if (m_guizmoOperation != ImGuizmo::SCALE)
					{
						m_guizmoOperation = ImGuizmo::SCALE;
					}
					else
					{
						m_usingGuizmo = false;
					}
				}
				else
				{
					m_guizmoOperation = ImGuizmo::SCALE;
					m_usingGuizmo = true;
				}
				break;
			case SE::Key::O:
				if (SE::Application::get().isKeyPressed(SE::Key::LeftControl) || SE::Application::get().isKeyPressed(SE::Key::RightControl))
				{
					openModelFromDialog();
				}
			case SE::Key::Delete:
				if (m_selectedComponent)
				{
					auto temp = m_selectedComponent->getActorOwner();
					m_selectedComponent->destroy();
					m_selectedComponent = temp->getRoot();
				}
			default:
				SE_CORE_TRACE("Key ({})", event.getKeyCode());
				break;
		}
		return false;
	}

	void EditorLayer::onUpdate(double deltaTime)
	{
		SE_PROFILE_FUNCTION();

		if (((uint32_t)m_framebuffer->getWidth() != (uint32_t)m_viewport.x() || (uint32_t)m_framebuffer->getHeight() != (uint32_t)m_viewport.y()) && (m_viewport.x()!=0 && m_viewport.y()!=0))
		{
			m_framebuffer->resize((uint32_t)m_viewport.x(), (uint32_t)m_viewport.y());
			m_editorCamera->setRatio((float)(m_viewport.x() / m_viewport.y()));
			//m_editorCamera->setRatio(4.f/3.f);
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
		ImGuizmo::SetImGuiContext(SE::Application::get().getImguiContext());

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
					openModelFromDialog();
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

			//SE::Vector2d mouseLoc = SE::Application::get().getMousePosition();
			//if (mouseLoc.x() > ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x && mouseLoc.y() > ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y && mouseLoc.x() < ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x + m_viewport.x() && mouseLoc.y() < ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y + m_viewport.y())
			//{
			//	SE::Application::get().getImGuiLayer()->setBlockEvent(false);
			//}
			bool m_viewportFocused = ImGui::IsWindowFocused();
			bool m_viewportHovered = ImGui::IsWindowHovered();
			SE::Application::get().getImGuiLayer()->setBlockEvent(!m_viewportFocused && !m_viewportHovered);

			if (m_usingGuizmo && m_selectedComponent)
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();
				ImGuizmo::SetRect(ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x, ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y, m_viewport.x(), m_viewport.y());

				// Snapping
				bool snapping = SE::Application::get().isKeyPressed(SE::Key::LeftControl);
				float snapIntervals[3] = { m_guizmoOperation==ImGuizmo::ROTATE ? 22.5f : 0.5f, m_guizmoOperation == ImGuizmo::ROTATE ? 22.5f : 0.5f, m_guizmoOperation == ImGuizmo::ROTATE ? 22.5f : 0.5f };

				const glm::mat4& camProj = m_editorCamera->getProjection();
				const glm::mat4& camView = m_editorCamera->getView();
				glm::mat4 transform = m_selectedComponent->getLocalTransform();
				glm::mat4 offset = m_selectedComponent->getParentTransform();
				//ImGuizmo::DrawCubes(glm::value_ptr(camView), glm::value_ptr(camProj), glm::value_ptr(transform), 1);
				//ImGuizmo::DrawGrid(glm::value_ptr(camView), glm::value_ptr(camProj), glm::value_ptr(transform), 5.f);
				ImGuizmo::Manipulate(glm::value_ptr(camView), glm::value_ptr(camProj), m_guizmoOperation, ImGuizmo::WORLD, glm::value_ptr(transform), (float*)glm::value_ptr(offset), snapping ? snapIntervals : nullptr);

				if (ImGuizmo::IsUsing())
				{
					glm::vec3 translation, rotation, scale;
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));
					rotation = glm::radians(rotation);

					glm::vec3 deltaRotation = rotation - m_selectedComponent->getRotation().getGlm();
					m_selectedComponent->setLocation(SE::Vector3f(translation));
					m_selectedComponent->addRotation(SE::Vector3f(deltaRotation));
					m_selectedComponent->setScale(SE::Vector3f(scale));
				}
			}
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
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create actor"))
				{
					m_currentScene->registerActor(new SE::Actor());
				}
					

				ImGui::EndPopup();
			}
			std::vector<SE::Actor*>* actors = m_currentScene->getRegisteredActors();
			uint32_t index = 0;
			for (std::vector<SE::Actor*>::iterator it = actors->begin(); it != actors->end(); it++, index++)
			{
				ImGuiTreeNodeFlags flags = ((m_selectedComponent==(*it)->getRoot()) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
				bool opened = ImGui::TreeNodeEx((void*)index, flags, (*it)->getName());
				if (ImGui::IsItemClicked())
				{
					m_selectedComponent = (*it)->getRoot();
				}
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
			if (ImGui::Button("Add component"))
			{
				ImGui::OpenPopup("Popup");
			};
			if (ImGui::BeginPopup("Popup"))
			{
				if (ImGui::MenuItem("Mesh"))
				{
					if (m_selectedComponent)
					{
						SE::Mesh* mesh = new SE::Mesh();
						SE::MeshComponent* meshComponent = new SE::MeshComponent(m_selectedComponent, mesh);
						m_selectedComponent->addComponent<SE::MeshComponent>(meshComponent);
					}
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Particle system"))
				{
					if (m_selectedComponent)
					{
						SE::ParticleEmitterComponent* particleEmitterComponent = new SE::ParticleEmitterComponent(m_selectedComponent);
						m_selectedComponent->addComponent<SE::ParticleEmitterComponent>(particleEmitterComponent);
						m_currentScene->registerRenderedComponent(particleEmitterComponent, true);
					}
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
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
		if ((std::find(m_actorComponentRecursiveStack.begin(), m_actorComponentRecursiveStack.end(), component) != m_actorComponentRecursiveStack.end()) && (true))
		{
			ImGuiTreeNodeFlags flags = ((m_selectedComponent == component) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
			bool opened = ImGui::TreeNodeEx((void*)0, flags, "Recursion error");
			if (ImGui::IsItemClicked())
			{
				SE::SceneComponent* sceneComponent = static_cast<SE::SceneComponent*>(component);
				if (sceneComponent)
				{
					m_selectedComponent = sceneComponent;
				}
			}
			if (opened)
			{
				ImGui::TreePop();
			}
			return;
		}
		m_actorComponentRecursiveStack.push_back(component);
		m_actorComponentRecursiveDepth++;
		uint32_t count = component->getComponentCount();
		ImGuiTreeNodeFlags flags = ((m_selectedComponent == component) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | (count == 1 ? 0 : ImGuiTreeNodeFlags_Leaf);
		bool opened = ImGui::TreeNodeEx((void*)0, flags, component->getName());
		if (ImGui::IsItemClicked())
		{
			SE::SceneComponent* sceneComponent = static_cast<SE::SceneComponent*>(component);
			if (sceneComponent)
			{
				m_selectedComponent = sceneComponent;
			}
		}
		if (opened)
		{
			for (uint32_t j = 0; j < count; j++)
			{
				EditorLayer::drawActorComponentInList(component->getComponent<SE::ActorComponent>(j));
			}
			ImGui::TreePop();
		}
	};

	void EditorLayer::openModelFromDialog()
	{
		std::string path = SE::openFile("");
		if (!path.empty())
		{
			std::vector<SE::Actor*> actorList = m_currentScene->importFBX(path.c_str());
			m_selectedComponent = actorList[actorList.size() - 1]->getRoot();
		}
	}
}