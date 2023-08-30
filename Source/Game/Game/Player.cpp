#pragma once
#include "Player.h"
#include "Input/InputSystem.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float rotate = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A))
		{
			rotate = -1;
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

		// fire weapon
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			auto weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();

			auto weapon2 = INSTANTIATE(Weapon, "Rocket");
			weapon2->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
			weapon2->Initialize();
			
			m_scene->Add(std::move(weapon));
			m_scene->Add(std::move(weapon2));
		}
	} 

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			kiko::EventManager::Instance().DispatchEvent("OnPlayerDeath", 0);
		}

		if (other->tag == "Boss")
		{
			destroyed = true;
			kiko::EventManager::Instance().DispatchEvent("OnPlayerDeath", 0);
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}


