#pragma once
#ifndef __SPRITE_SHEET__
#define __SPRITE_SHEET__
#include <vector>
#include "Frame.h"
#include <unordered_map>
#include <SDL.h>

class SpriteSheet {

	private:
	std::string m_name;

	std::unordered_map<std::string, Frame> m_frames;

	SDL_Texture *m_texture;

	public:

	SpriteSheet(std::string _name, SDL_Texture *_texture);
	SpriteSheet(std::string _name);
	~SpriteSheet();

	// getters
	Frame GetFrame(const std::string &_frameName);
	SDL_Texture *getTexture() const;

	// setters
	void addFrame(const Frame &frame);
	void setTexture(SDL_Texture *texture);

};

#endif /* defined (__SPRITE_SHEET__) */