#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Editor/EditorCamera.hpp>

namespace SpringEditor
{
	enum class SE_EDITOR_PANELS {
		VIEWPORT,
		PROPERTIES,
		OUTLINER
	};
	class EditorLayer : public SE::Layer
	{
	public:
		EditorLayer();

		virtual ~EditorLayer();

		virtual void onAttach() override;
		virtual void onEvent(SE::Event& e) override;
		bool EditorLayer::onKeyPressedEvent(SE::KeyPressedEvent& event);
		bool EditorLayer::onMouseButtonPressedEvent(SE::MousePressed& event);
		bool EditorLayer::onMouseButtonReleasedEvent(SE::MouseReleased& event);

		virtual void onUpdate(double deltaTime) override;
		virtual void onImGuiRender() override;
		
		void drawActorComponentInList(SE::ActorComponent* component);

		void openModelFromDialog();
		void openModelFromDialogToMeshComponent();

		void openScene();
		void saveScene();

	private:
		SE::Vector2<float> m_viewport;
		SE::Framebuffer* m_framebuffer;
		SE::Framebuffer* m_deferredbuffer;
		std::shared_ptr<SE::Scene> m_currentScene;
		EditorCamera* m_editorCamera;
		SE::SceneComponent* m_selectedComponent;
		SE::SceneComponent* m_hoveredComponent;
		uint32_t m_actorComponentRecursiveDepth;
		std::vector<SE::ActorComponent*> m_actorComponentRecursiveStack;
		ImGuizmo::OPERATION m_guizmoOperation;
		ImGuizmo::MODE m_guizmoSpace;
		bool m_usingGuizmo;
		bool m_draggingGuizmo;
		bool m_changedSelection;
		enum SE_EDITOR_PANELS m_hoveredPanel;
		float m_viewportLimits[4] = { 0.0, 0.0, 100.0, 100.0 };
		int m_pixelData;
	};
}