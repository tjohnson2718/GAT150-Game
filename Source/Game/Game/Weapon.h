#pragma once
//#include "Framework/Components/PhysicsComponent.h"
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
		//void Read(const json_t& value);

	private:
		float speed = 0;
		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}

