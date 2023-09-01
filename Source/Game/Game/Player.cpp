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

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		//transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		//transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

		if ((transform.position.x < 0 || transform.position.x >(float)kiko::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)kiko::g_renderer.GetHeight()))
		{
			transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
			transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}
		
		fireTimer += dt;
		superTimer += dt;

 		
			// fire weapon
 		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			if (fireTimer >= fireRate)
			{
				auto weapon = INSTANTIATE(Weapon, "Rocket");
				weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));

				fireTimer = 0;
			}
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_F) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_F))
		{
			if (superTimer >= superRate)
			{
				auto super = INSTANTIATE(Weapon, "Super");
				super->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
				super->Initialize();
				m_scene->Add(std::move(super));

				
				superTimer = 0;
			}
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

		if (other->tag == "PowerUp")
		{
			kiko::EventManager::Instance().DispatchEvent("OnAddLives", 0);
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, fireRate);
		READ_DATA(value, superRate);
	}
}


