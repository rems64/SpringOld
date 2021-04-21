#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	SceneComponent::SceneComponent(ActorComponent* owner) : ActorComponent(owner), m_location(0.0, 0.0, 0.0), m_rotation(0.0, 0.0, 0.0), m_scale(1.0, 1.0, 1.0), m_transform(), m_hierarchicalTransform(glm::mat4(1.0f)), m_isRoot(false)
	{
		updateTransform();
	}

	SceneComponent::SceneComponent(Actor* owner, bool root) : ActorComponent(), m_location(0.0, 0.0, 0.0), m_rotation(0.0, 0.0, 0.0), m_scale(1.0, 1.0, 1.0), m_transform(), m_hierarchicalTransform(glm::mat4(1.0f)), m_isRoot(root), m_actorRoot(owner)
	{
		updateTransform();
	}

	SceneComponent::~SceneComponent()
	{
	}

	void SceneComponent::updateTransform()
	{
		m_transform = glm::translate(glm::mat4(1.0f), m_location.getGlm()) * glm::toMat4(glm::quat(m_rotation.getGlm())) * glm::scale(glm::mat4(1.0f), m_scale.getGlm());
		onUpdateTransform();
	}

	void SceneComponent::onUpdateTransform()
	{
		for (ActorComponent* component : m_components)
		{
			SceneComponent* sceneComponent = static_cast<SceneComponent*>(component);
			if (sceneComponent)
			{
				sceneComponent->updateHierarchicalTransform(&(m_hierarchicalTransform * m_transform));
			}
		}
	}

	void SceneComponent::updateHierarchicalTransform(glm::mat4* transform)
	{
		m_hierarchicalTransform = *transform;
		for (ActorComponent* component : m_components)
		{
			SceneComponent* sceneComponent = static_cast<SceneComponent*>(component);
			if (sceneComponent)
			{
				sceneComponent->updateHierarchicalTransform(&(m_hierarchicalTransform * m_transform));
			}
		}
	}

	Actor* SceneComponent::getActorOwner()
	{
		if (m_isRoot)
		{
			return m_actorRoot;
		}
		else
		{
			return static_cast<SceneComponent*>(getOwner())->getActorOwner();
		}
	}

	void SceneComponent::destroy()
	{
		if (m_isRoot)
		{
			SE_CORE_ERROR("Root");
		}
		else
		{
			getOwner()->removeComponent(this);
			postDestroy();
			delete this;
		}
	}
}