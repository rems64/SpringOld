#pragma once

#include <SpringEngine/core.hpp>

#include <SpringEngine/Core/RenderedComponent.hpp>
#include <SpringEngine/Core/ParticleEmitter.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API ParticleEmitterComponent : public RenderedComponent
	{
	public:
		ParticleEmitterComponent(ActorComponent* owner);
		virtual ~ParticleEmitterComponent();

		virtual int drawCall() const override;

		virtual void tick(double deltaSeconds) override;

		virtual void postDestroy() override;

	protected:
		virtual void onUpdateTransform() override;

	private:
		ParticleEmitter* m_instance;
	};
}