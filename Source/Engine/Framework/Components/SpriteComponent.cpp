#include "SpriteComponent.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

	void SpriteComponent::Update(float dt)
	{
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}

