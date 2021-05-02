#pragma once

#include <SpringEngine/SpringEngine.hpp>

class EditorCamera : public SE::Actor
{
public:
	EditorCamera();
	~EditorCamera();

	virtual void tick(double deltaSecond) override;
	SE::CameraComponent* getCamera() { return m_cameraComponent; };

	//glm::quat getOrientation() const { return glm::quat(glm::vec3()); };
protected:
	SE::CameraComponent* m_cameraComponent;
	SE::Vector2<float> m_previousMouseLoc;
};