#pragma once
//#include "Framework/Components/Component.h"
#include "Framework/Framework.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:

		/*Weapon(float speed, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 1.0f;
		}*/

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* actor);
		void Read(const json_t& value);

	private:
		float speed = 0;

	};
}

