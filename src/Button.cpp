#include "Button.h"
#include <utility>
#include "TextureManager.h"


/**
 * @brief Construct a new Button:: Button object
 * 
 * @param image_path 
 * @param button_name 
 * @param type 
 * @param position 
 * @param is_centered 
 */
Button::Button(const std::string& image_path, std::string button_name, const GameObjectType type,
               const glm::vec2 position, const bool is_centered):
m_alpha(255), m_name(std::move(button_name)), m_isCentered(is_centered), m_active(true)
{
	TextureManager::Instance()->load(image_path,m_name);

	const auto size = TextureManager::Instance()->getTextureSize(m_name);
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = position;
	setType(type);
}

Button::~Button()
= default;

void Button::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the button
	TextureManager::Instance()->draw(m_name, x, y, 0, m_alpha, m_isCentered);
}

void Button::update()
{
	//check if mouse is over the Button
	onMouseOver();

	// check if mouse outside the Button
	onMouseOut();

	// check if left mouse is clicked
	onLeftMouseButtonClick();
}

void Button::clean()
{
}

/**
 * @brief sets the alpha transparency of the button
 * @param alpha
 * @return void
 */
void Button::setAlpha(const Uint8 alpha)
{
	m_alpha = alpha;
}

/**
 * @brief sets the button active boolean
 * @return void
 */
void Button::setActive(const bool value)
{
	m_active = value;
}
