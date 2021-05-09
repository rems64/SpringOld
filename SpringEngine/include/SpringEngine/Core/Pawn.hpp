#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Core/Actor.hpp>

namespace SE
{
	class SE_API Pawn : public Actor
	{
	public:
		Pawn();
		~Pawn();
		virtual void onEvent(Event& event) override;
	};
}