#pragma once

#include <SpringEngine/Core/Application.hpp>

#ifdef SE_PLATEFORM_WINDOWS

extern SE::Application* SE::CreateApplication();

int main()
{
	SE::Application* app = SE::CreateApplication();
	app->mainLoop();
	delete app;
}

#endif