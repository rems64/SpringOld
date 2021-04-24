#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

class FlightSimulatorApp : public SE::Application
{
public:
	FlightSimulatorApp() : SE::Application("ISU Flight simulator")
	{
		SE_PROFILE_FUNCTION();
#ifndef NDEBUG
		m_worldLayer = new SE::WorldLayer();
		pushLayer(m_worldLayer);
		pushLayer(new SE::DebugUILayer("UI Debug"));
#endif
	}

	SE::Scene* getScene() { return m_worldLayer->getScene(); };
	private:
		SE::WorldLayer* m_worldLayer;

	~FlightSimulatorApp()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	FlightSimulatorApp* application = new FlightSimulatorApp();
	std::vector<SE::Actor*> actors = application->getScene()->importFBX("ressources/shuttle.fbx");
	application->getScene()->registerRenderedComponent(actors[0]->getComponent<SE::MeshComponent>(0));
	return application;
}