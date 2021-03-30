#include <SpringEngine/SpringEngine.hpp>

class FlightSimulatorApp : public SE::Application
{
public:
	FlightSimulatorApp() : SE::Application("Flight simulator")
	{
		pushLayer(new SE::DebugUILayer("UI Debug"));
	}

	~FlightSimulatorApp()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	SE::Application* application = new FlightSimulatorApp();
	application->getDataManager()->loadFBX("ressources/sample.fbx", application->getCurrentScene());
	return application;
}