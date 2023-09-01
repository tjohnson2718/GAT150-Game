#include "PowerUp.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	CLASS_DEFINITION(PowerUp);

	bool PowerUp::Initialize()
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

	void PowerUp::Update(float dt)
	{
		Actor::Update(dt);

		if ((transform.position.x < 0 || transform.position.x >(float)kiko::g_renderer.GetWidth()) ||
			(transform.position.y < 0 || transform.position.y >(float)kiko::g_renderer.GetHeight()))
		{
			transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
			transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

			m_physicsComponent->SetPosition(transform.position);
		}
	}

	void PowerUp::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player")
		{
			destroyed = true;
		}
	}

	void PowerUp::Read(const json_t& value)
	{
		Actor::Read(value);
	}
}