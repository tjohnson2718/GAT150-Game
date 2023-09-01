#pragma once
#include "Framework/framework.h"
namespace kiko
{
	class PowerUp : public Actor
	{
	public:
		CLASS_DECLARATION(PowerUp);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}