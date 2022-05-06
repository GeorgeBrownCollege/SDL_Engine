#pragma once
#ifndef __LABEL__
#define __LABEL__

#include <string>

#include "UIControl.h"
#include "FontManager.h"

/**
 * \brief Label Class - Inherits from UIControl
 */
class Label final : public UIControl
{
public:
	explicit Label(const std::string& text = "Default Label Text", const std::string& font_name = "lazy", int size = 20, SDL_Color colour = {0, 0, 0, 255}, glm::vec2 position = glm::vec2(), int font_style = TTF_STYLE_NORMAL, bool is_centered = true);
	~Label() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// Mutator Functions 
	void SetText(const std::string& new_text);
	void SetColour(SDL_Color new_colour) const;
	void SetSize(int new_size);

private:
	// private data members
	std::string m_fontPath;
	std::string m_fontID;
	SDL_Color m_fontColour;
	std::string m_fontName;
	std::string m_text;
	bool m_isCentered = true;
	int m_fontSize;
	int m_fontStyle;

	// private functions
	void BuildFontID();
};

#endif /* defined (__LABEL__) */