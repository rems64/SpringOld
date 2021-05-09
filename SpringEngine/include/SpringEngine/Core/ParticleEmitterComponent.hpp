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
		ParticleEmitterComponent(SceneComponent* owner);
		virtual ~ParticleEmitterComponent();

		virtual int drawCall() const override;

		virtual void editorUpdate(double deltaSeconds) override;
		virtual void update(double deltaSeconds) override;

		virtual void postDestroy() override;

	private:
		ParticleEmitter* m_instance;
	};
}