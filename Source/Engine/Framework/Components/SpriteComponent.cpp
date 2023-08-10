#include "SpriteComponent.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

void kiko::SpriteComponent::Update(float dt)
{
}

void kiko::SpriteComponent::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
}
