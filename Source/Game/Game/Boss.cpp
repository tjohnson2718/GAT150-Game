#include "Boss.h"
#include "Player.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Boss);

	bool Boss::Initialize()
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

	void Boss::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::Vector2 direction = player->transform.position - transform.position;
			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());
			m_physicsComponent->ApplyTorque(turnAngle);
		}

		m_physicsComponent->ApplyForce(forward * speed);

		if ((transform.position.x < 0 || transform.position.x >(float)kiko::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)kiko::g_renderer.GetHeight()))
		{
			transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
			transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}
	}

	void Boss::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player" || other->tag == "Weapon")
		{
			lives--;

			if (lives <= 0)
			{
				destroyed = true;
				kiko::EventManager::Instance().DispatchEvent("OnBossDeath", 0);
			}
		}

		if (other->tag == "Super")
		{
			lives -= 20;

			if (lives <= 0)
			{
				destroyed = true;
				kiko::EventManager::Instance().DispatchEvent("OnBossDeath", 0);
			}
		}

		std::cout << "Boss Lives: " << lives << std::endl;
		
	}

	void Boss::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, lives);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}

