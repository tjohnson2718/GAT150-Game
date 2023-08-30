#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;

	private:
		float speed = 0;
		float turnRate = 0;
		float fireRate = 0;
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
