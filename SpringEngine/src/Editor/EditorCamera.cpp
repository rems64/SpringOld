#include <SpringEngine/Editor/EditorCamera.hpp>

EditorCamera::EditorCamera() : SE::Actor(), m_previousMouseLoc(0.0f, 0.0f), m_cameraTargetLocation(0.0f, 0.0f, 0.0f)
{
	setName("Editor Camera");
	m_editorCameraComponent = new SE::EditorCameraComponent(this, true);
	//m_rootComponent->addComponent<SE::CameraComponent>(m_cameraComponent);
	delete m_rootComponent;
	m_rootComponent = m_editorCameraComponent;
	m_editorCameraComponent->setRoot(true);
}

EditorCamera::~EditorCamera()
{

}

void EditorCamera::editorUpdate(double deltaSeconds)
{
	if (SE::Application::get().getInputManager()->isKeyPressed(SE::Key::LeftAlt) || SE::Application::get().getInputManager()->isKeyPressed(SE::Key::RightAlt))
	{
		const SE::Vector2<float> mouseLoc(SE::Application::get().getMousePosition());
		SE::Vector2<float> delta = (mouseLoc - m_previousMouseLoc) * 0.003f;
		m_previousMouseLoc = mouseLoc;

		if (SE::Application::get().getInputManager()->isMouseButtonDown(SE::Mouse::ButtonLeft))
		{
			float yawSign = m_editorCameraComponent->getUp().y() < 0 ? -1.0f : 1.0f;
			m_editorCameraComponent->m_yaw += yawSign * delta.x() * 0.8f;
			m_editorCameraComponent->m_pitch += delta.y() * 0.8f;
		}
		else if (SE::Application::get().getInputManager()->isMouseButtonDown(SE::Mouse::ButtonMiddle))
		{
			float x = std::min(m_editorCameraComponent->m_viewportWidth / 1000.0f, 2.4f);
			float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

			float y = std::min(m_editorCameraComponent->m_viewportHeight / 1000.0f, 2.4f);
			float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;
			m_editorCameraComponent->m_cameraTargetPoint += m_editorCameraComponent->getRight() * delta.x() * m_editorCameraComponent->m_distance * xFactor * -1.0f;
			m_editorCameraComponent->m_cameraTargetPoint += m_editorCameraComponent->getUp() * delta.y() * m_editorCameraComponent->m_distance * yFactor;
		}
		else if (SE::Application::get().getInputManager()->isMouseButtonDown(SE::Mouse::ButtonRight))
		{
			float distance = m_editorCameraComponent->m_distance * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f);
			m_editorCameraComponent->m_distance -= delta.y() * speed;
			if (m_editorCameraComponent->m_distance < 1.0f)
			{
				m_editorCameraComponent->m_cameraTargetPoint += m_editorCameraComponent->getForward();
				m_editorCameraComponent->m_distance = 1.0f;
			}
		}
	}
}