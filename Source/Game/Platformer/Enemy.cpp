#pragma once
#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A))
		{
			dir = -1;
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		kiko::vec2 forward = kiko::vec2{ -1, 0 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * dir);

		// Jump
		bool onGround = (groundCount > 0);

		if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			kiko::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
		}

		if (other->tag == "Ground") groundCount++;
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}


