#include <SpringEditor/EditorCamera.hpp>

EditorCamera::EditorCamera() : SE::Actor()
{
	setName("Editor Camera");
	m_cameraComponent = new SE::CameraComponent(m_rootComponent);
	m_rootComponent->addComponent<SE::CameraComponent>(m_cameraComponent);
}

EditorCamera::~EditorCamera()
{

}