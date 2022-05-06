#include "Label.h"
#include "TextureManager.h"

Label::Label(const std::string& text, const std::string& font_name, const int font_size, const SDL_Color colour, const glm::vec2 position, const int font_style, const bool is_centered):
	m_fontColour(colour), m_fontName(font_name), m_text(text), m_isCentered(is_centered), m_fontSize(font_size), m_fontStyle(font_style)
{
	m_fontPath = "../Assets/fonts/" + font_name + ".ttf";

	BuildFontID();

	// Load font, convert Label String to Texture and store in TextureManager
	FontManager::Instance().Load(m_fontPath, m_fontID, font_size, font_style);
	FontManager::Instance().TextToTexture(text, m_fontID, m_fontID, colour);

	// set Size of Label Object based on computed Texture Size 
	const auto size = TextureManager::Instance().GetTextureSize(m_fontID);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	// set the position of the Label 
	GetTransform()->position = position;
}

Label::~Label()
= default;

void Label::Draw()
{
	// draw the label
	TextureManager::Instance().DrawText(m_fontID, GetTransform()->position, 0, 255, m_isCentered);
}

void Label::Update()
{
}

void Label::Clean()
{
}

/**
 * \brief This function sets the Text value of the Label
 * \param new_text 
 */
void Label::SetText(const std::string& new_text)
{
	m_text = new_text;
	BuildFontID();

	FontManager::Instance().Load(m_fontPath, m_fontID, m_fontSize, m_fontStyle);
	FontManager::Instance().TextToTexture(new_text, m_fontID, m_fontID, m_fontColour);
	const auto size = TextureManager::Instance().GetTextureSize(m_fontID);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
}

/**
 * \brief This function sets the colour value of the Label
 * \param new_colour 
 */
void Label::SetColour(const SDL_Color new_colour) const
{
	FontManager::Instance().Load(m_fontPath, m_fontID, m_fontSize, m_fontStyle);
	FontManager::Instance().TextToTexture(m_text, m_fontID, m_fontID, new_colour);
}

/**
 * \brief 
 * \param new_size 
 */
void Label::SetSize(const int new_size)
{
	m_fontSize = new_size;

	BuildFontID();
	
	FontManager::Instance().Load(m_fontPath, m_fontID, m_fontSize, TTF_STYLE_NORMAL);
	FontManager::Instance().TextToTexture(m_text, m_fontID, m_fontID, m_fontColour);
	const auto size = TextureManager::Instance().GetTextureSize(m_fontID);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
}

/**
 * \brief Private function that builds a font id to be used with TextureManager
 */
void Label::BuildFontID()
{
	m_fontID = m_fontName;
	m_fontID += "-";
	m_fontID += std::to_string(m_fontSize);
	m_fontID += "-";
	m_fontID += m_text;
}

