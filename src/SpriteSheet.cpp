#include "SpriteSheet.h"

#include <utility>

SpriteSheet::SpriteSheet(std::string name, SDL_Texture* texture)
	:m_name(std::move(name)), m_texture(texture)
{}

SpriteSheet::SpriteSheet(std::string name)
	:m_name(std::move(name)), m_texture(nullptr)
{
}

SpriteSheet::~SpriteSheet()
= default;

//Returns the frame of the m_frames map at the string key from the parameter.
Frame SpriteSheet::getFrame(const std::string& frame_name)
{
	return m_frames[frame_name];
}

SDL_Texture* SpriteSheet::getTexture() const
{
	return m_texture;
}

void SpriteSheet::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
}

//Adds a Frame struct object to m_frames vector using the parameter Frame struct objects name as the key
void SpriteSheet::addFrame(const Frame& frame)
{
	m_frames[frame.name] = frame;
}
