#pragma once

#include <GLFW/glfw3.h>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Core/Input.hpp>

namespace SE
{
	class Application;
	class SE_API InputManager
	{
	public:
		InputManager();
		~InputManager() = default;

		void setLinkedApp(Application* app);
		bool isKeyPressed(const KeyCode key);
		bool isMouseButtonDown(const MouseCode button);

		float getAxis(uint32_t index)
		{
			return m_axis[index].getValue(this);
		}
	private:
		Application* m_linkedApp;
		std::vector<Axis> m_axis;
	};
}