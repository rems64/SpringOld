#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

class FlightSimulatorApp : public SE::Application
{
public:
	FlightSimulatorApp() : SE::Application("ISU Flight simulator")
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
	application->getCurrentScene()->importFBX("ressources/textured.fbx")[0]->getComponent<MeshComponent>(0)->setLocation(Vector3f(1.0f, 0.0f, 0.0f));
	application->getCurrentScene()->importFBX("ressources/textured.fbx")[0]->getComponent<MeshComponent>(0)->setLocation(Vector3f(-1.0f, 0.0f, 0.0f));
	return application;
}