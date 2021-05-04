#pragma once

#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/EditorCameraComponent.hpp>

class SE_API EditorCamera : public SE::Actor
{
public:
	EditorCamera();
	~EditorCamera();

	virtual void tick(double deltaSecond) override;
	SE::CameraComponent* getCamera() { return dynamic_cast<SE::CameraComponent*>(m_editorCameraComponent); };

	//glm::quat getOrientation() const { return glm::quat(glm::vec3()); };
protected:
	SE::EditorCameraComponent* m_editorCameraComponent;
	SE::Vector2<float> m_previousMouseLoc;
	SE::Vector3<float> m_cameraTargetLocation;
};