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

inline bool TextureManager::TextureExists(const std::string & id)
{
	return m_textureMap.find(id) != m_textureMap.end();
}

bool TextureManager::SpriteSheetExists(const std::string & sprite_sheet_name)
{
	return m_spriteSheetMap.find(sprite_sheet_name) != m_spriteSheetMap.end();
}

bool TextureManager::Load(const std::string & file_name, const std::string & id)
{
	if (TextureExists(id))
	{
		return true;
	}

	const auto temp_surface(Config::MakeResource(IMG_Load(file_name.c_str())));
	if (temp_surface == nullptr)
	{
		return false;
	}

	// everything went ok, add the texture to our list
	if (const auto texture(Config::MakeResource(SDL_CreateTextureFromSurface(Renderer::Instance().GetRenderer(), temp_surface.get()))); 
		texture != nullptr)
	{
		m_textureMap[id] = texture;
		return true;
	}
	return false;
}

bool TextureManager::LoadSpriteSheet(
	const std::string & data_file_name,
	const std::string & texture_file_name,
	const std::string & sprite_sheet_name)
{
	std::fstream data_file; // create file stream object
	const std::string delimiter = " ";

	// open the text data file
	data_file.open(data_file_name, std::ios::in);

	// create a new spritesheet object and allocate memory for it
	auto sprite_sheet = new SpriteSheet(sprite_sheet_name);

	// if the file successfully opened
	if (data_file)
	{
		std::string input_line;
		// read one line at a time
		while (std::getline(data_file, input_line))
		{
			Frame frame;
			size_t line_position = 0;
			std::vector<std::string> tokens;

			for (auto i = 0; i < 5; ++i)
			{
				line_position = input_line.find(delimiter);
				tokens.push_back(input_line.substr(0, line_position));
				input_line.erase(0, line_position + 1);
			}

			frame.name = tokens[0];
			frame.x = std::stoi(tokens[1]);
			frame.y = std::stoi(tokens[2]);
			frame.w = std::stoi(tokens[3]);
			frame.h = std::stoi(tokens[4]);

			// add the new frame to the spritesheet
			sprite_sheet->AddFrame(frame);
		}
	}
	else
	{
		std::cout << "error opening file" << std::endl;
		return false;
	}

	data_file.close();

	// load the sprite texture and store it in the textureMap
	Load(texture_file_name, sprite_sheet_name);

	// get a pointer to the Texture and store it in the new spritesheet object
	sprite_sheet->SetTexture(GetTexture(sprite_sheet_name));

	// store the new spritesheet in the spriteSheetMap
	m_spriteSheetMap[sprite_sheet_name] = sprite_sheet;

	// cleanup
	sprite_sheet = nullptr;

	return true;
}

void TextureManager::Draw(const std::string & id, const int x, const int y, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect src_rect{};
	SDL_Rect dest_rect{};

	src_rect.x = 0;
	src_rect.y = 0;

	int texture_width;
	int texture_height;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &texture_width, &texture_height);

	src_rect.w = dest_rect.w = texture_width;
	src_rect.h = dest_rect.h = texture_height;

	if (centered) {
		const auto x_offset = static_cast<int>(texture_width * 0.5);
		const auto y_offset = static_cast<int>(texture_height * 0.5);
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), static_cast<Uint8>(alpha));
	SDL_RenderCopyEx(Renderer::Instance().GetRenderer(), m_textureMap[id].get(), &src_rect, &dest_rect, angle, nullptr, flip);
}

void TextureManager::Draw(const std::string& id, const glm::vec2 position, const double angle, const int alpha, const bool centered,
                          const SDL_RendererFlip flip)
{
	Draw(id, static_cast<int>(position.x), static_cast<int>(position.y), angle, alpha, centered, flip);
}

void TextureManager::Draw(const std::string& id, const int x, const int y, const GameObject* go, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect src_rect{};
	SDL_Rect dest_rect{};

	int texture_width, texture_height;
	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &texture_width, &texture_height);
	src_rect = { 0, 0, texture_width, texture_height };
	dest_rect.w = go->GetWidth();
	dest_rect.h = go->GetHeight();

	if (centered) {
		const int x_offset = static_cast<int>(dest_rect.w * 0.5);
		const int y_offset = static_cast<int>(dest_rect.h * 0.5);
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), static_cast<Uint8>(alpha));
	SDL_RenderCopyEx(Renderer::Instance().GetRenderer(), m_textureMap[id].get(), &src_rect, &dest_rect, angle, nullptr, flip);
}

void TextureManager::DrawFrame(const std::string & id, const int x, const int y, const int frame_width,
                               const int frame_height, int& current_row,
                               int& current_frame, const int frame_number, const int row_number,
                               const float speed_factor, const double angle,
                               const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	AnimateFrames(frame_width, frame_height, frame_number, row_number, speed_factor, current_frame, current_row);

	SDL_Rect src_rect{};
	SDL_Rect dest_rect{};

	src_rect.x = 0;
	src_rect.y = 0;

	// frame_height size
	const auto texture_width = frame_width;
	const auto texture_height = frame_height;

	// starting point of the where we are looking
	src_rect.x = texture_width * current_frame;
	src_rect.y = texture_height * current_row;

	src_rect.w = texture_width;
	src_rect.h = texture_height;

	dest_rect.w = texture_width;
	dest_rect.h = texture_height;

	if (centered) {
		const int x_offset = static_cast<int>(dest_rect.w * 0.5);
		const int y_offset = static_cast<int>(dest_rect.h * 0.5);
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), static_cast<Uint8>(alpha));
	SDL_RenderCopyEx(Renderer::Instance().GetRenderer(), m_textureMap[id].get(), &src_rect, &dest_rect, angle, nullptr, flip);
}

void TextureManager::AnimateFrames(int frame_width, int frame_height, const int frame_number, const int row_number, const float speed_factor, int& current_frame, int& current_row) const
{
	const auto total_frames = static_cast<float>(frame_number * row_number);
	const int animation_rate = static_cast<int>(round(total_frames / 2.0f / speed_factor));

	if (frame_number > 1)
	{
		if (Game::Instance().GetFrames() % animation_rate == 0)
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

void TextureManager::PlayAnimation(
	const std::string & sprite_sheet_name, Animation & animation,
	const int x, const int y, const float speed_factor,
	const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	const auto total_frames = static_cast<float>(animation.frames.size());
	const int animation_rate = static_cast<int>(round(total_frames / 2.0f / speed_factor));

	if (total_frames > 1)
	{
		if (Game::Instance().GetFrames() % animation_rate == 0)
		{
			animation.current_frame++;
			if (static_cast<float>(animation.current_frame) > total_frames - 1)
			{
				animation.current_frame = 0;
			}
		}
	}

	SDL_Rect src_rect{};
	SDL_Rect dest_rect{};

	src_rect.x = 0;
	src_rect.y = 0;

	// frame_height size
	const auto texture_width = animation.frames[animation.current_frame].w;
	const auto texture_height = animation.frames[animation.current_frame].h;

	// starting point of the where we are looking
	src_rect.x = animation.frames[animation.current_frame].x;
	src_rect.y = animation.frames[animation.current_frame].y;

	src_rect.w = animation.frames[animation.current_frame].w;
	src_rect.h = animation.frames[animation.current_frame].h;

	dest_rect.w = texture_width;
	dest_rect.h = texture_height;

	if (centered) {
		const int x_offset = static_cast<int>(dest_rect.w * 0.5);
		const int y_offset = static_cast<int>(dest_rect.h * 0.5);
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[sprite_sheet_name].get(), static_cast<Uint8>(alpha));
	SDL_RenderCopyEx(Renderer::Instance().GetRenderer(), m_textureMap[sprite_sheet_name].get(), &src_rect, &dest_rect, angle, nullptr, flip);
}

void TextureManager::PlayAnimation(const std::string& sprite_sheet_name, Animation& animation, const glm::vec2 position,
	const float speed_factor, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	PlayAnimation(sprite_sheet_name, animation, static_cast<int>(position.x), static_cast<int>(position.y), speed_factor, angle, alpha, centered, flip);
}

void TextureManager::DrawText(const std::string & id, const int x, const int y, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect src_rect{};
	SDL_Rect dest_rect{};

	src_rect.x = 0;
	src_rect.y = 0;

	int texture_width;
	int texture_height;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &texture_width, &texture_height);

	src_rect.w = dest_rect.w = texture_width;
	src_rect.h = dest_rect.h = texture_height;

	if (centered) {
		const int x_offset = static_cast<int>(dest_rect.w * 0.5);
		const int y_offset = static_cast<int>(dest_rect.h * 0.5);
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), static_cast<Uint8>(alpha));
	SDL_RenderCopyEx(Renderer::Instance().GetRenderer(), m_textureMap[id].get(), &src_rect, &dest_rect, angle, nullptr, flip);
}

void TextureManager::DrawText(const std::string& id, const glm::vec2 position, const double angle, const int alpha, const bool centered,
                              const SDL_RendererFlip flip)
{
	DrawText(id, static_cast<int>(position.x), static_cast<int>(position.y), angle, alpha, centered, flip);
}

glm::vec2 TextureManager::GetTextureSize(const std::string & id)
{
	int width;
	int height;
	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &width, &height);

	return { static_cast<float>(width), static_cast<float>(height) };
}

void TextureManager::SetAlpha(const std::string & id, const Uint8 new_alpha)
{
	std::shared_ptr<SDL_Texture> texture = m_textureMap[id];
	SDL_SetTextureAlphaMod(texture.get(), new_alpha);
	texture = nullptr;
}

void TextureManager::SetColour(const std::string & id, const Uint8 red, const Uint8 green, const Uint8 blue)
{
	std::shared_ptr<SDL_Texture> texture = m_textureMap[id];
	SDL_SetTextureColorMod(texture.get(), red, green, blue);
	texture = nullptr;
}

bool TextureManager::AddTexture(const std::string & id, std::shared_ptr<SDL_Texture> texture)
{
	if (TextureExists(id))
	{
		return true;
	}

	m_textureMap[id] = std::move(texture);

	return true;
}

SDL_Texture* TextureManager::GetTexture(const std::string & id)
{
	return m_textureMap[id].get();
}

void TextureManager::RemoveTexture(const std::string & id)
{
	m_textureMap.erase(id);
}

int TextureManager::GetTextureMapSize() const
{
	return static_cast<int>(m_textureMap.size());
}

void TextureManager::Clean()
{
	m_textureMap.clear();
	std::cout << "TextureMap Cleared,  TextureMap Size: " << m_textureMap.size() << std::endl;

	m_spriteSheetMap.clear();
	std::cout << "Existing SpriteSheets Cleared" << std::endl;
}

void TextureManager::DisplayTextureMap()
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

SpriteSheet* TextureManager::GetSpriteSheet(const std::string & name)
{
	return m_spriteSheetMap[name];
}

