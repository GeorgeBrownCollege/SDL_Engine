#include "SpriteSheet.h"

#include <utility>

SpriteSheet::SpriteSheet(std::string _name, SDL_Texture *_texture)
	:m_name(std::move(_name)), m_texture(_texture) { }

SpriteSheet::SpriteSheet(std::string _name)
	: m_name(std::move(_name)), m_texture(nullptr) { }

SpriteSheet::~SpriteSheet()
= default;

Frame SpriteSheet::GetFrame(const std::string & _frameName) {
	return m_frames[_frameName];
}

SDL_Texture *SpriteSheet::getTexture() const {
	return m_texture;
}

void SpriteSheet::setTexture(SDL_Texture * _texture) {
	m_texture = _texture;
}

void SpriteSheet::addFrame(const Frame & _frame) {
	m_frames[_frame.m_name] = _frame;
}
