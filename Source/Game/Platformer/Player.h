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
		void OnCollisionExit(Actor* other) override;


	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
