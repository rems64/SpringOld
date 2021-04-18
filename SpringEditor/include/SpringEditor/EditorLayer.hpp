#include <SpringEngine/SpringEngine.hpp>

namespace SpringEditor
{
	class EditorLayer : public SE::Layer
	{
	public:
		EditorLayer();

		virtual ~EditorLayer();

		virtual void onAttach() override;
		virtual void onEvent(SE::Event& e) override;

		virtual void onUpdate(double deltaTime) override;
		virtual void onImGuiRender() override;
		
		void drawActorComponentInList(SE::ActorComponent* component);
	private:
		SE::Vector2<float> m_viewport;
		SE::Framebuffer* m_framebuffer;
		std::shared_ptr<SE::Scene> m_currentScene;
		SE::Texture* m_tmpImage;
		SE::CameraComponent* m_editorCamera;
		uint32_t m_actorComponentRecursiveDepth;
		std::vector<SE::ActorComponent*> m_actorComponentRecursiveStack;
		float m_temp;
	};
}