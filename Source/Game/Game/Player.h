#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player);
		
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		float fireRate = 0.0f;
		float fireTimer = 0.0f;
		float superRate = 0.0f;
		float superTimer = 0.0f;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
