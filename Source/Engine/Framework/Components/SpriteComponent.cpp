#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
namespace kiko
{
	void SpriteComponent::Update(float dt)
	{
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		//renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->transfrom.position.y, RadianToDegrees(_owner->m_transform.rotation));
	}
}


