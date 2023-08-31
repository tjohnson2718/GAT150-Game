#pragma once
#include "Enemy.h"

namespace kiko
{
	class Boss : public Enemy
	{
	public:
		CLASS_DECLARATION(Boss);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;

	public:
		int lives = 0;
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
