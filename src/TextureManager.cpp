#include "TextureManager.h"
#include <SDL_image.h>
#include "Game.h"
#include <utility>
#include <fstream>
#include <sstream>
#include "Frame.h"
#include <iterator>
#include "Renderer.h"

TextureManager::TextureManager()
= default;

TextureManager::~TextureManager()
= default;

inline bool TextureManager::m_textureExists(const std::string & id)
{
	return m_textureMap.find(id) != m_textureMap.end();
}

bool TextureManager::m_spriteSheetExists(const std::string & sprite_sheet_name)
{
	return m_spriteSheetMap.find(sprite_sheet_name) != m_spriteSheetMap.end();
}

bool TextureManager::load(const std::string & file_name, const std::string & id)
{
	if (m_textureExists(id))
	{
		return true;
	}

	const auto pTempSurface(Config::make_resource(IMG_Load(file_name.c_str())));


	if (pTempSurface == nullptr)
	{
		return false;
	}

	const auto pTexture(Config::make_resource(SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), pTempSurface.get())));

	// everything went ok, add the texture to our list
	if (pTexture != nullptr)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

bool TextureManager::loadSpriteSheet(
	const std::string & data_file_name,
	const std::string & texture_file_name,
	const std::string & sprite_sheet_name)
{
	std::string inputLine;
	std::fstream dataFile; // create file stream object
	std::string delimeter = " ";

	// open the text data file
	dataFile.open(data_file_name, std::ios::in);

	// create a new spritesheet object and allocate memory for it
	auto spriteSheet = new SpriteSheet(sprite_sheet_name);

	// if the file successfully opened
	if (dataFile)
	{
		// read one line at a time
		while (std::getline(dataFile, inputLine))
		{
			Frame frame;
			size_t linePosition = 0;
			std::vector<std::string> tokens;

			for (auto i = 0; i < 5; ++i)
			{
				linePosition = inputLine.find(delimeter);
				tokens.push_back(inputLine.substr(0, linePosition));
				inputLine.erase(0, linePosition + 1);
			}

			frame.name = tokens[0];
			frame.x = std::stoi(tokens[1]);
			frame.y = std::stoi(tokens[2]);
			frame.w = std::stoi(tokens[3]);
			frame.h = std::stoi(tokens[4]);

			// add the new frame to the spritesheet
			spriteSheet->addFrame(frame);
		}
	}
	else
	{
		std::cout << "error opening file" << std::endl;
		return false;
	}

	dataFile.close();

	// load the sprite texture and store it in the textureMap
	load(texture_file_name, sprite_sheet_name);

	// get a pointer to the Texture and store it in the new spritesheet object
	spriteSheet->setTexture(getTexture(sprite_sheet_name));

	// store the new spritesheet in the spriteSheetMap
	m_spriteSheetMap[sprite_sheet_name] = spriteSheet;

	// cleanup
	spriteSheet = nullptr;

	return true;
}

void TextureManager::draw(const std::string & id, const int x, const int y, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(Renderer::Instance().getRenderer(), m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
}

void TextureManager::drawFrame(const std::string & id, const int x, const int y, const int frame_width,
	const int frame_height, int& current_row,
	int& current_frame, int frame_number, int row_number,
	float speed_factor, const double angle,
	const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	animateFrames(frame_width, frame_height, frame_number, row_number, speed_factor, current_frame, current_row);

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	// frame_height size
	const auto textureWidth = frame_width;
	const auto textureHeight = frame_height;

	// starting point of the where we are looking
	srcRect.x = textureWidth * current_frame;
	srcRect.y = textureHeight * current_row;

	srcRect.w = textureWidth;
	srcRect.h = textureHeight;

	destRect.w = textureWidth;
	destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(Renderer::Instance().getRenderer(), m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
}

void TextureManager::animateFrames(int frame_width, int frame_height, const int frame_number, const int row_number, const float speed_factor, int& current_frame, int& current_row)
{
	const auto totalFrames = frame_number * row_number;
	const int animationRate = round(totalFrames / 2 / speed_factor);


	if (frame_number > 1)
	{
		if (TheGame::Instance().getFrames() % animationRate == 0)
		{
			current_frame++;
			if (current_frame > frame_number - 1)
			{
				current_frame = 0;
				current_row++;
			}
			if (current_row > row_number - 1)
			{
				current_row = 0;
			}
		}
	}

}

void TextureManager::playAnimation(
	const std::string & sprite_sheet_name, Animation & animation,
	int x, int y, float speed_factor,
	double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	const auto totalFrames = animation.frames.size();
	const int animationRate = round(totalFrames / 2 / speed_factor);

	if (totalFrames > 1)
	{
		if (TheGame::Instance().getFrames() % animationRate == 0)
		{
			animation.current_frame++;
			if (animation.current_frame > totalFrames - 1)
			{
				animation.current_frame = 0;
			}
		}
	}

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	// frame_height size
	const auto textureWidth = animation.frames[animation.current_frame].w;
	const auto textureHeight = animation.frames[animation.current_frame].h;

	// starting point of the where we are looking
	srcRect.x = animation.frames[animation.current_frame].x;
	srcRect.y = animation.frames[animation.current_frame].y;

	srcRect.w = animation.frames[animation.current_frame].w;
	srcRect.h = animation.frames[animation.current_frame].h;

	destRect.w = textureWidth;
	destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[sprite_sheet_name].get(), alpha);
	SDL_RenderCopyEx(Renderer::Instance().getRenderer(), m_textureMap[sprite_sheet_name].get(), &srcRect, &destRect, angle, nullptr, flip);
}

void TextureManager::drawText(const std::string & id, const int x, const int y, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(Renderer::Instance().getRenderer(), m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
}

glm::vec2 TextureManager::getTextureSize(const std::string & id)
{
	int width, height;
	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &width, &height);
	glm::vec2 size;

	size.x = width;
	size.y = height;

	return size;
}

void TextureManager::setAlpha(const std::string & id, const Uint8 new_alpha)
{
	auto pTexture = m_textureMap[id];
	SDL_SetTextureAlphaMod(pTexture.get(), new_alpha);
	pTexture = nullptr;
}

void TextureManager::setColour(const std::string & id, const Uint8 red, const Uint8 green, const Uint8 blue)
{
	auto pTexture = m_textureMap[id];
	SDL_SetTextureColorMod(pTexture.get(), red, green, blue);
	pTexture = nullptr;
}

bool TextureManager::addTexture(const std::string & id, std::shared_ptr<SDL_Texture> texture)
{
	if (m_textureExists(id))
	{
		return true;
	}

	m_textureMap[id] = std::move(texture);

	return true;
}

SDL_Texture* TextureManager::getTexture(const std::string & id)
{
	return m_textureMap[id].get();
}

void TextureManager::removeTexture(const std::string & id)
{
	m_textureMap.erase(id);
}

int TextureManager::getTextureMapSize() const
{
	return m_textureMap.size();
}

void TextureManager::clean()
{
	m_textureMap.clear();
	std::cout << "TextureMap Cleared,  TextureMap Size: " << m_textureMap.size() << std::endl;

	m_spriteSheetMap.clear();
	std::cout << "Existing SpriteSheets Cleared" << std::endl;
}

void TextureManager::displayTextureMap()
{
	std::cout << "------------ Displaying Texture Map -----------" << std::endl;
	std::cout << "Texture Map size: " << m_textureMap.size() << std::endl;
	auto it = m_textureMap.begin();
	while (it != m_textureMap.end())
	{
		std::cout << it->first << std::endl;
		++it;
	}
}

SpriteSheet* TextureManager::getSpriteSheet(const std::string & name)
{
	return m_spriteSheetMap[name];
}

