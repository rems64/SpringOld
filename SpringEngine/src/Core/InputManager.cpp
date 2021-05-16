#include <SpringEngine/Core/InputManager.hpp>
#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	InputManager::InputManager() : m_axis({}), m_linkedApp(nullptr)
	{
	}

	void InputManager::setLinkedApp(Application* app)
	{
		m_linkedApp = app;
		Axis moveForward;
		moveForward.addContributor(Key::Z,  1.0);
		moveForward.addContributor(Key::S, -1.0);
		m_axis.emplace_back(moveForward);

		Axis moveRight;
		moveRight.addContributor(Key::D,  1.0);
		moveRight.addContributor(Key::Q, -1.0);
		m_axis.emplace_back(moveRight);

		Axis turn;
		turn.addContributor(Key::A, -1.0);
		turn.addContributor(Key::E,  1.0);
		m_axis.emplace_back(turn);
	}
	bool InputManager::isKeyPressed(const KeyCode key)
	{
		auto state = glfwGetKey((GLFWwindow*)m_linkedApp->getMainWindow().getNativeWindow(), static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool InputManager::isMouseButtonDown(const MouseCode button)
	{
		auto state = glfwGetMouseButton((GLFWwindow*)m_linkedApp->getMainWindow().getNativeWindow(), static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}
}