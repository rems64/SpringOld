#pragma once

#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/Core/ActorComponent.hpp>

namespace SE
{
	class Scene;
	class Actor;
	class SE_API SceneComponent : public ActorComponent
	{
	public:
		SceneComponent(ActorComponent* owner);
		SceneComponent(Actor* owner, bool root);
		virtual ~SceneComponent();

		void setLocation(Vector3f& loc) { m_location = loc; updateTransform(); };
		void setRotation(Vector3f& rot) { m_rotation = rot; updateTransform(); };
		void setScale(Vector3f& scale) { m_scale = scale; updateTransform(); };

		void addLocation(Vector3f& loc) { m_location += loc; updateTransform(); };
		void addRotation(Vector3f& rot) { m_rotation += rot; updateTransform(); };
		void addScale(Vector3f& scale) { m_scale += scale; updateTransform(); };

		Vector3f getLocation() { return m_location; };
		Vector3f getRotation() { return m_rotation; };
		Vector3f getScale() { return m_scale; };

		Vector3f& getLocationRef() { return m_location; };
		Vector3f& getRotationRef() { return m_rotation; };
		Vector3f& getScaleRef() { return m_scale; };

		virtual void updateTransform();
		virtual glm::mat4 getTransform() const { return m_hierarchicalTransform * m_transform; };
		virtual glm::mat4 getLocalTransform() const { return m_transform; };
		virtual glm::mat4 getParentTransform() const { return m_hierarchicalTransform; };

		virtual void updateHierarchicalTransform(glm::mat4* transform);

		virtual ActorComponent* getOwner() override { return (m_isRoot ? nullptr : m_owner); };
		virtual Actor* getRootActor() { return m_actorRoot; };

		Actor* getActorOwner();

		bool isRoot() { return m_isRoot; };

		virtual void destroy() override;

	protected:
		virtual void onUpdateTransform();

		//Scene* m_scene;
		bool m_isRoot;
		Actor* m_actorRoot;
		Vector3f m_location;
		Vector3f m_rotation;
		Vector3f m_scale;
		glm::mat4 m_transform;
		glm::mat4 m_hierarchicalTransform;
	};
}