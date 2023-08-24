#pragma once
#include "PhysicsComponent.h"
namespace kiko
{
	//CLASS_DEFINITION(EnginePhysicsComponent)

	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)

		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;
	};
}