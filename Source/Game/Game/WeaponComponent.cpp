#include "WeaponComponent.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	bool WeaponComponent::Initialize()
	{
		auto collisionComponent = m_owner->GetComponent<kiko::CollisionComponent>();
		if (collisionComponent )

	}
	void WeaponComponent::Update(float dt)
	{
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_owner->transform.rotation);
		m_owner->transform.position += forward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
		m_owner->transform.position.x = kiko::Wrap(m_owner->transform.position.x, (float)kiko::g_renderer.GetWidth());
		m_owner->transform.position.y = kiko::Wrap(m_owner->transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void WeaponComponent::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}

	void WeaponComponent::OnCollision(Actor* other)
	{
		m_owner->destroyed = true;
	}

}
