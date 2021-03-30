#pragma once

#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/SceneElement.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class Scene;
	class SE_API Renderer
	{
	public:
		static void renderSceneElement(SceneElement* element);
		static void renderScene(Scene* scene, double deltaMillis);
	private:

	};
}