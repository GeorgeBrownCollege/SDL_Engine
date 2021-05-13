#include "FontManager.h"
#include "Renderer.h"
#include "TextureManager.h"

FontManager* FontManager::s_pInstance = nullptr;

inline bool FontManager::m_exists(const std::string& id)
{
	return m_fontMap.find(id) != m_fontMap.end();
}

bool FontManager::load(const std::string& file_name, const std::string& id, const int size, const int style)
{
	if (m_exists(id))
	{
		return true;
	}

	const auto font(Config::make_resource(TTF_OpenFont(file_name.c_str(), size)));
	if (font != nullptr)
	{
		TTF_SetFontStyle(font.get(), style);
		m_fontMap[id] = font;
		return true;
	}

	return false;
}

bool FontManager::textToTexture(const std::string& text, const std::string& font_id, const std::string& texture_id, const SDL_Color colour)
{
	//Render text surface

	const auto textSurface(Config::make_resource(TTF_RenderText_Solid(m_fontMap[font_id].get(), text.c_str(), colour)));

	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		const auto pTexture(Config::make_resource(SDL_CreateTextureFromSurface(/* TheGame::Instance()->getRenderer()*/ Renderer::Instance().getRenderer(), textSurface.get())));

		//Create texture from surface pixels
		TextureManager::Instance().addTexture(texture_id, pTexture);
		if (TextureManager::Instance().getTexture(texture_id) == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}

	return true;
}

TTF_Font* FontManager::getFont(const std::string& id)
{
	return m_fontMap[id].get();
}

void FontManager::clean()
{
	m_fontMap.clear();
}

void FontManager::displayFontMap()
{
	std::cout << "------------ Displaying Font Map -----------" << std::endl;

	std::cout << "Font Map size: " << m_fontMap.size() << std::endl;

	auto it = m_fontMap.begin();
	while (it != m_fontMap.end())
	{
		std::cout << " " << it->first << std::endl;
		++it;
	}
}


FontManager::FontManager()
= default;

FontManager::~FontManager()
= default;
