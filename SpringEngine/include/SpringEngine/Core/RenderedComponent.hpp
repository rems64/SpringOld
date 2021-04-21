#pragma once
#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API RenderedComponent : public SceneComponent
	{
	public:
		RenderedComponent(ActorComponent* owner);
		virtual ~RenderedComponent();

		virtual int drawCall() const = 0; // Called by the rendered, return the number of sub-drawcalls

	private:

	};
}