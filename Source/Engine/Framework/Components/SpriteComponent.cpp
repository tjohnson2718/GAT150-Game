#include "SpriteComponent.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Framework/ResourceManager.h"

namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::Initialize()
	{
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value)
	{
		READ_DATA(value, texutreName);
	}
}

