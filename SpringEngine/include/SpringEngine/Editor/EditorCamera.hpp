#pragma once

#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/EditorCameraComponent.hpp>

class SE_API EditorCamera : public SE::Actor
{
public:
	EditorCamera();
	~EditorCamera();

	virtual void editorUpdate(double deltaSecond) override;
	SE::CameraComponent* getCamera() { return dynamic_cast<SE::CameraComponent*>(m_editorCameraComponent); };
	void setTarget(SE::Vector3f& loc) { m_editorCameraComponent->setTarget(loc); };

	//glm::quat getOrientation() const { return glm::quat(glm::vec3()); };
protected:
	SE::EditorCameraComponent* m_editorCameraComponent;
	SE::Vector2f m_previousMouseLoc;
	SE::Vector3f m_cameraTargetLocation;
};