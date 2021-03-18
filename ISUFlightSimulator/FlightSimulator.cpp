//#include <iostream>
//#include <SpringEngine/Misc/Logger.hpp>
//
//#include <SpringEngine/Core/Application.hpp>
//#include <SpringEngine/Layers/DebugUILayer.hpp>
//
//int main()
//{
//	SE::Application* app = new SE::Application("App de test");
//	SE_CORE_LOG_LEVEL(SE::LOG_LVL::SE_LOGLVL_INFO);
//	app->getMainWindow().setVSync(true);
//	
//	SE::DebugUILayer* uiDebugLayer = new SE::DebugUILayer("UI Debug");
//	app->pushOverlay(uiDebugLayer);
//
//	app->mainLoop();
//	delete app;
//	return 0;
//}