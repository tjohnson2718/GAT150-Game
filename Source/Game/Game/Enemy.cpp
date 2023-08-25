#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
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

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::Vector2 direction = player->transform.position - transform.position;
			transform.rotation = direction.Angle() + kiko::HalfPi;
		}


		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * speed * kiko::g_time.GetDeltaTime();

		m_physicsComponent->ApplyForce(forward * speed);

		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, fireRate);
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		//Player* p = dynamic_cast<Player*>(other)
		if (other->tag == "Player")
		{
			kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
			//m_game->AddPoints(100);
			destroyed = true;

			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = kiko::Color{ 1, 1, 1, 1 };

			kiko::Transform transform{ { this->transform.position.x }, 0, 1 };
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->lifespan = 1.0f;

			m_scene->Add(std::move(emitter));
		}
	}
}

