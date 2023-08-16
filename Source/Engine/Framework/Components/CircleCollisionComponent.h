#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		//CLASS_DECLARATION(CircleCollisionComponent)

		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collisoin) override;

	};
}