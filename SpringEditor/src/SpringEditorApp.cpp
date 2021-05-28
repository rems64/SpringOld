#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

#include <SpringEditor/EditorLayer.hpp>

class SpringEditorApp : public SE::Application
{
public:
	SpringEditorApp() : SE::Application("Spring editor")
	{
		SE_PROFILE_FUNCTION();
#ifndef NDEBUG
		pushLayer(new SE::DebugUILayer("UI Debug"));
#endif
		pushLayer(new SpringEditor::EditorLayer());
	}

	~SpringEditorApp()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	SE::Application* application = new SpringEditorApp();
	application->getMainWindow().setVSync(true);
	//application->getCurrentScene()->importFBX("ressources/textured.fbx");
	return application;
}