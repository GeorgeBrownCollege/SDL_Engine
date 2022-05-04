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
	explicit SpriteSheet(std::string name);
	~SpriteSheet();

	// getters
	Frame GetFrame(const std::string& frame_name);
	[[nodiscard]] SDL_Texture* GetTexture() const;

	// setters
	void AddFrame(const Frame& frame);
	void SetTexture(SDL_Texture* texture);
	
private:
	std::string m_name;

	std::unordered_map<std::string, Frame> m_frames;

	SDL_Texture* m_pTexture;
};

#endif /* defined (__SPRITE_SHEET__) */