#include <SpringEditor/EditorCamera.hpp>

EditorCamera::EditorCamera() : SE::Actor(), m_previousMouseLoc(0.0f, 0.0f)
{
	setName("Editor Camera");
	m_cameraComponent = new SE::CameraComponent(this, true);
	//m_rootComponent->addComponent<SE::CameraComponent>(m_cameraComponent);
	delete m_rootComponent;
	m_rootComponent = m_cameraComponent;
	m_cameraComponent->setRoot(true);
}

EditorCamera::~EditorCamera()
{

}

void EditorCamera::tick(double deltaSeconds)
{
	if (SE::Application::get().isKeyPressed(SE::Key::LeftAlt) || SE::Application::get().isKeyPressed(SE::Key::RightAlt))
	{
		const SE::Vector2<float> mouseLoc(SE::Application::get().getMousePosition());
		SE::Vector2<float> delta = (mouseLoc - m_previousMouseLoc) * 0.01f;
		m_previousMouseLoc = mouseLoc;

		if (SE::Application::get().isMouseButtonDown(SE::Mouse::ButtonLeft))
		{

		}
		else if (SE::Application::get().isMouseButtonDown(SE::Mouse::ButtonMiddle))
		{
			SE::Vector3f& loc = m_rootComponent->getLocationRef();
			loc += m_rootComponent->getRight() * (float)delta.x() * -1.0f;
			loc += m_rootComponent->getUp() * (float)delta.y();
			m_rootComponent->updateTransform();
		}
		else if (SE::Application::get().isMouseButtonDown(SE::Mouse::ButtonRight))
		{
			SE::Vector3f& loc = m_rootComponent->getLocationRef();
			loc += m_rootComponent->getForward() * (float)delta.y() * 2.0f;
			m_rootComponent->updateTransform();
		}
	}
}