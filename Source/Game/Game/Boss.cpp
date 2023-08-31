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

		if (lives == 80 || lives == 60 || lives == 40 || lives == 20)
		{
			auto weapon = INSTANTIATE(Weapon, "LaserBeam");
			weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();

			m_scene->Add(std::move(weapon));
		}

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

		std::cout << "Boss Lives: " << lives << std::endl;
		
	}

	void Boss::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, lives);
	}
}

