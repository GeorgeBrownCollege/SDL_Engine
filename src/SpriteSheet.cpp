#include "SpriteSheet.h"

#include <utility>

SpriteSheet::SpriteSheet(std::string name, SDL_Texture* texture)
	:m_name(std::move(name)), m_pTexture(texture)
{}

SpriteSheet::SpriteSheet(std::string name)
	:m_name(std::move(name)), m_pTexture(nullptr)
{
}

SpriteSheet::~SpriteSheet()
= default;

Frame SpriteSheet::GetFrame(const std::string& frame_name)
{
	return m_frames[frame_name];
}

SDL_Texture* SpriteSheet::GetTexture() const
{
	return m_pTexture;
}

void SpriteSheet::SetTexture(SDL_Texture* texture)
{
	m_pTexture = texture;
}

void SpriteSheet::AddFrame(const Frame& frame)
{
	m_frames[frame.name] = frame;
}
