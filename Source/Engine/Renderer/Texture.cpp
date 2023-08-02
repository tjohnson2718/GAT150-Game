#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG("file not found")
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("invalid texture")
			return false;
		}
		return true;
	}

	//vec2 Texture::GetSize()
	//{
	//	// ASSERT texture is not null
	//	//SDL_Point point;
	//	// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
	//	//SDL_QueryTexture(<get point.x and point.y, use link above>);
	//	//return vec2{ point.x, point.y };
	//}
}