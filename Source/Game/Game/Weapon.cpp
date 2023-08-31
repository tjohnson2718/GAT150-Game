#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon);

	bool Weapon::Initialize()
	{
		Actor::Initialize();
		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);
	
		// if you want to wrap put it here

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
		Actor::Read(value);

		READ_DATA(value, speed);
	}

}
