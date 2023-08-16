#pragma once
#include "PhysicsComponent.h"
namespace kiko
{
	CLASS_DEFINITION(EnginePhysicsComponent)

	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
	};
}