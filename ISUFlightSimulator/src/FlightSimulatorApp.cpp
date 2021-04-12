#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

class FlightSimulatorApp : public SE::Application
{
public:
	FlightSimulatorApp() : SE::Application("Flight simulator")
	{
		SE_PROFILE_FUNCTION();
#ifndef NDEBUG
		pushLayer(new SE::DebugUILayer("UI Debug"));
#endif
	}

	~FlightSimulatorApp()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	SE::Application* application = new FlightSimulatorApp();
	application->getCurrentScene()->importFBX("ressources/textured.fbx");
	return application;
}