#include <SpringEngine/Core/Input.hpp>

#include <SpringEngine/Core/InputManager.hpp>

namespace SE
{
	float Axis::getValue(InputManager* inputManager)
	{
		float value = 0.0;
		for (std::pair<KeyCode, float> pair : contributors)
		{
			value += (inputManager->isKeyPressed(pair.first) ? 1.0 : 0.0) * pair.second;
		}
		return value;
	}
}