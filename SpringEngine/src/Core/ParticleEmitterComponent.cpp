#include <SpringEngine/Core/ParticleEmitterComponent.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	ParticleEmitterComponent::ParticleEmitterComponent(ActorComponent* owner) : RenderedComponent(owner), m_instance(new ParticleEmitter(this))
	{
		m_instance->getMaterial()->updateShaderUniforms();
	}

	ParticleEmitterComponent::~ParticleEmitterComponent()
	{
	}

	int ParticleEmitterComponent::drawCall() const
	{
		m_instance->drawCall();
		//Renderer::drawStripInstanced(4, m_instance->getCount(), m_instance->getMaterial(), &getTransform());
		m_instance->getMaterial()->bind();
		m_instance->getMaterial()->bindTextures();
		glDisable(GL_DEPTH_TEST);
		Renderer::drawIndexedInstanced(m_instance->getCount(), 6, m_instance->getIndices(), m_instance->getMaterial(), &getTransform());
		glEnable(GL_DEPTH_TEST);
		m_instance->getMaterial()->unbindTextures();
		m_instance->getMaterial()->unbind();
		return 1;
	}


	void ParticleEmitterComponent::tick(double deltaSeconds)
	{
		m_instance->update(deltaSeconds);
		for (auto component : m_components)
		{
			component->tick(deltaSeconds);
		}
	}

	void ParticleEmitterComponent::postDestroy()
	{
		getActorOwner()->getScene()->unregisterRenderedComponent(this);
	}
}