#pragma once

#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/SceneElement.hpp>

#include <SpringEngine/core.hpp>

namespace SE
{
	class SE_API Renderer
	{
	public:
		static void renderSceneElement(SceneElement* element);
	private:

	};
}