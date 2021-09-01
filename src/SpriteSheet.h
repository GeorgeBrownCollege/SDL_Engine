#pragma once
#ifndef __SPRITE_SHEET__
#define __SPRITE_SHEET__
#include <vector>
#include "Frame.h"
#include <unordered_map>
#include <SDL.h>

/*
 *SpriteSheet Class is used by Sprite Class to store the animated objects
 *sprite sheet. This Class has a map of the frames that have been
 *sliced out of the sprite sheet in the loadSpriteSheet function in the
 *TextureManager Class which is called from Sprite objects such as the
 *Player Class to create animations.
 */

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