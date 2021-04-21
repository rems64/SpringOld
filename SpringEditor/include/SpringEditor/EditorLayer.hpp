#include <SpringEngine/SpringEngine.hpp>

namespace SpringEditor
{
	enum class SE_EDITOR_PANELS {
		VIEWPORT,
		PROPERTIES
	};
	class EditorLayer : public SE::Layer
	{
	public:
		EditorLayer();

		virtual ~EditorLayer();

		virtual void onAttach() override;
		virtual void onEvent(SE::Event& e) override;
		bool EditorLayer::onKeyPressedEvent(SE::KeyPressedEvent& event);

		virtual void onUpdate(double deltaTime) override;
		virtual void onImGuiRender() override;
		
		void drawActorComponentInList(SE::ActorComponent* component);

		void openModelFromDialog();

	private:
		SE::Vector2<float> m_viewport;
		SE::Framebuffer* m_framebuffer;
		std::shared_ptr<SE::Scene> m_currentScene;
		SE::CameraComponent* m_editorCamera;
		SE::SceneComponent* m_selectedComponent;
		uint32_t m_actorComponentRecursiveDepth;
		std::vector<SE::ActorComponent*> m_actorComponentRecursiveStack;
		ImGuizmo::OPERATION m_guizmoOperation;
		bool m_usingGuizmo;
	};
}