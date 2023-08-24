#include "TextRenderComponent.h"

namespace kiko
{
	CLASS_DEFINITION(TextRenderComponent);

	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other)
	{
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;

		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}

	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty())
		{
			m_text = std::make_unique<kiko::Text>();
		}

		return false;
	}

	void TextRenderComponent::Read(const json_t& value)
	{
		RenderComponent::Read(value);
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
	}

	void TextRenderComponent::Update(float dt)
	{
	}

	void TextRenderComponent::Draw(Renderer& renderer)
	{
	}

	void TextRenderComponent::SetText(const std::string& string)
	{
	}
}