#pragma once
#ifndef __SPRITE_SHEET__
#define __SPRITE_SHEET__
#include <vector>
#include "Frame.h"
#include <unordered_map>
#include <SDL.h>

class SpriteSheet
{
public:
	SpriteSheet(std::string name, SDL_Texture* texture);
	SpriteSheet(std::string name);
	~SpriteSheet();

	// getters
	Frame getFrame(const std::string& frame_name);
	SDL_Texture* getTexture() const;

	// setters
	void addFrame(const Frame& frame);
	void setTexture(SDL_Texture* texture);
	
private:
	std::string m_name;

	std::unordered_map<std::string, Frame> m_frames;

	SDL_Texture* m_texture;
};

#endif /* defined (__SPRITE_SHEET__) */