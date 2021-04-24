#pragma once

#include <SpringEngine/SpringEngine.hpp>

class EditorCamera : public SE::Actor
{
public:
	EditorCamera();
	~EditorCamera();

	SE::CameraComponent* getCamera() { return m_cameraComponent; };
protected:
	SE::CameraComponent* m_cameraComponent;
};