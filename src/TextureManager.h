#pragma once
#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

// Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/vec2.hpp"

// SDL Libraries
#include<SDL.h>

#include "Config.h"
#include "SpriteSheet.h"
#include "Animation.h"

/* Singleton */
class TextureManager
{
public:
	static TextureManager& Instance()
	{
		static TextureManager instance;
		return instance;
	}

	// loading functions
	bool load(const std::string& file_name, const std::string& id);
	bool loadSpriteSheet(const std::string& data_file_name, const std::string& texture_file_name, const std::string& sprite_sheet_name);

	// drawing functions
	void draw(const std::string& id, int x, int y, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int frame_width, int frame_height,
		int& current_row, int& current_frame, int frame_number, int row_number, float speed_factor,
		double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawText(const std::string& id, int x, int y, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// animation functions
	void animateFrames(int frame_width, int frame_height, int frame_number, int row_number, float speed_factor, int& current_frame, int& current_row);
	void playAnimation(const std::string& sprite_sheet_name, Animation& animation, int x, int y, float speed_factor, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SpriteSheet* getSpriteSheet(const std::string& name);

	// texture utility functions
	SDL_Texture* getTexture(const std::string& id);
	void setColour(const std::string& id, Uint8 red, Uint8 green, Uint8 blue);
	bool addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture);
	void removeTexture(const std::string& id);
	glm::vec2 getTextureSize(const std::string& id);
	void setAlpha(const std::string& id, Uint8 new_alpha);

	// textureMap functions
	int getTextureMapSize() const;
	void displayTextureMap();
	void clean();


private:

	TextureManager();
	~TextureManager();

	// private utility functions
	bool m_textureExists(const std::string& id);
	bool m_spriteSheetExists(const std::string& sprite_sheet_name);

	// storage structures
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textureMap;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheetMap;
};

#endif /* defined(__TEXTURE_MANAGER__) */