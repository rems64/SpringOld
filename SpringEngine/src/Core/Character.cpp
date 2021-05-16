#include <SpringEngine/Core/Character.hpp>

#include <SpringEngine/Core/SceneComponent.hpp>
#include <SpringEngine/Core/MeshComponent.hpp>
#include <SpringEngine/Core/Mesh.hpp>
#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Core/InputManager.hpp>

namespace SE
{
	Character::Character() : Pawn()
	{
		setName("Default character");
		Mesh* mesh = new Mesh();
		m_characterMesh = new MeshComponent(m_rootComponent, mesh);
		m_characterMesh->setName("Character mesh");
		addComponent<MeshComponent>(m_characterMesh);
	}

	Character::~Character()
	{
	}

	void Character::onEvent(Event& event)
	{
		SE::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<SE::KeyPressedEvent>(SE_BIND_EVENT(Character::onKeyPressedEvent));
	}

	int Character::onKeyPressedEvent(KeyPressedEvent& event)
	{
		switch (event.getKeyCode())
		{
		case SE::Key::Space:
			jump();
			return 1;
		default:
			return 0;
		}
	}

	void Character::jump()
	{
		m_rootComponent->addLocation(Vector3f(0.0f, 0.0f, 1.0f));
	}

	void Character::moveForward(float factor)
	{
		m_rootComponent->addLocation(m_rootComponent->getForward()* factor);
	}

	void Character::update(double deltaTime)
	{
		m_rootComponent->addLocation(m_rootComponent->getForward() * SE::Application::get().getInputManager()->getAxis(0) * (float)deltaTime * 0.003f);
		m_rootComponent->addLocation(m_rootComponent->getRight() * SE::Application::get().getInputManager()->getAxis(1) * (float)deltaTime * 0.003f);
		m_rootComponent->addRotation(m_rootComponent->getUp() * SE::Application::get().getInputManager()->getAxis(2) * (float)deltaTime * -0.003f);
	}

	void Character::editorUpdate(double deltaTime)
	{
		m_rootComponent->addLocation(m_rootComponent->getForward() * SE::Application::get().getInputManager()->getAxis(0) * (float)deltaTime * 0.003f);
		m_rootComponent->addLocation(m_rootComponent->getRight() * SE::Application::get().getInputManager()->getAxis(1) * (float)deltaTime * 0.003f);
		m_rootComponent->addRotation(m_rootComponent->getUp() * SE::Application::get().getInputManager()->getAxis(2) * (float)deltaTime * -0.003f);
	}
}