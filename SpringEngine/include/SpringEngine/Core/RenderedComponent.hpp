#pragma once
#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class ActorComponent;
	class DirectionalLightComponent;
	class SE_API RenderedComponent : public SceneComponent
	{
	public:
		RenderedComponent(SceneComponent* owner);
		virtual ~RenderedComponent();

		virtual int drawCall() const = 0; // Called by the rendered
		virtual int shadowPassCall(DirectionalLightComponent* light) const = 0; // Called by the rendered

		virtual void postDestroy() override;

	private:

	};
}