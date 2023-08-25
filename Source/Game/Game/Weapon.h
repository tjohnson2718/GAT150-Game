#pragma once
#include "Framework/Framework.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* actor);

	private:
		float speed = 0;
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}

