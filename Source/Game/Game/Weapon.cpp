#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace kiko
{
	bool Weapon::Initialize()
	{
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

	void Weapon::Update(float dt)
	{
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag)
		{
			destroyed = true;
		}
	}

	void Weapon::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}

}
