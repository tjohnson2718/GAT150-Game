#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

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

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::Vector2 direction = player->transform.position - transform.position;
			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());
			m_physicsComponent->ApplyTorque(turnAngle);
			//transform.rotation = direction.Angle() + kiko::HalfPi;
		}


		//transform.position += forward * speed * speed * kiko::g_time.GetDeltaTime();

		m_physicsComponent->ApplyForce(forward * speed);

		//transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		//transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());
		if ((transform.position.x < 0 || transform.position.x >(float)kiko::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)kiko::g_renderer.GetHeight()))
		{
			transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
			transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}
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
		if (other->tag == "Player" || other->tag == "Weapon")
		{
			kiko::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
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

