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
#include "GameObject.h"

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
	bool Load(const std::string& file_name, const std::string& id);
	bool LoadSpriteSheet(const std::string& data_file_name, const std::string& texture_file_name, const std::string& sprite_sheet_name);

	// drawing functions
	void Draw(const std::string& id, int x, int y, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(const std::string& id, glm::vec2 position, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(const std::string& id, int x, int y, const GameObject* go, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(const std::string& id, int x, int y, int frame_width, int frame_height,
		int& current_row, int& current_frame, int frame_number, int row_number, float speed_factor,
		double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawText(const std::string& id, int x, int y, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawText(const std::string& id, glm::vec2 position, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// animation functions
	void AnimateFrames(int frame_width, int frame_height, int frame_number, int row_number, float speed_factor, int& current_frame, int& current_row) const;
	void PlayAnimation(const std::string& sprite_sheet_name, Animation& animation, int x, int y, float speed_factor, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void PlayAnimation(const std::string& sprite_sheet_name, Animation& animation, glm::vec2 position, float speed_factor, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SpriteSheet* GetSpriteSheet(const std::string& name);

	// texture utility functions
	SDL_Texture* GetTexture(const std::string& id);
	void SetColour(const std::string& id, Uint8 red, Uint8 green, Uint8 blue);
	bool AddTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture);
	void RemoveTexture(const std::string& id);
	glm::vec2 GetTextureSize(const std::string& id);
	void SetAlpha(const std::string& id, Uint8 new_alpha);

	// textureMap functions
	[[nodiscard]] int GetTextureMapSize() const;
	void DisplayTextureMap();
	void Clean();


private:

	TextureManager();
	~TextureManager();

	// private utility functions
	bool TextureExists(const std::string& id);
	bool SpriteSheetExists(const std::string& sprite_sheet_name);

	// storage structures
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textureMap;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheetMap;
};

#endif /* defined(__TEXTURE_MANAGER__) */