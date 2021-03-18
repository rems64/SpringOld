#include <SpringEngine/SpringEngine.hpp>

class FlightSimulatorApp : public SE::Application
{
public:
	FlightSimulatorApp() : SE::Application("Flight simulator")
	{

	}

	~FlightSimulatorApp()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	SE::Application* application = new FlightSimulatorApp();
	SE::DebugUILayer* uiDebugLayer = new SE::DebugUILayer("UI Debug");
	application->pushOverlay(uiDebugLayer);
	return application;
}