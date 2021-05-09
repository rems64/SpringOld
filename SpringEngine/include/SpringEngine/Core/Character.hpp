#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Pawn.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Events/KeyEvents.hpp>

namespace SE
{
	class SE_API Character : public Pawn
	{
	public:
		Character();
		~Character();
		
		virtual void onEvent(Event& event) override;
		void jump();
		void moveForward(float factor);

		virtual void update(double deltaTime) override;
		virtual void editorUpdate(double deltaTime) override;

	private:
		virtual int onKeyPressedEvent(KeyPressedEvent& event);
	};
}